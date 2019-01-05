#include <stdio.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>

int main(int argc, char *argv[])
{
	AVFormatContext *pFormatCtx;
    AVCodecContext* pCodecCtx;
    AVCodec         *pCodec;
    int i, videoindex;
    AVPacket *packet;
    int screen_w;
    int screen_h;
    FILE *record_h264;
    int write_ret;

	if (argc < 3){
		printf("please input file path.");
		return -1;
	}

	av_register_all();
    avformat_network_init();

	pFormatCtx = avformat_alloc_context();

	if(avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0){
        fprintf(stderr, "Couldn't open input stream.\n");
        return -1;
    }

    if(avformat_find_stream_info(pFormatCtx, NULL) < 0){
        fprintf(stderr, "Couldn't find stream information.\n");
        return -1;
    }

	videoindex=-1;
    for(i=0; i<pFormatCtx->nb_streams; i++) {
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            videoindex = i;
            printf("stream[%d]->code->codec_type = AVMEDIA_TYPE_VIDEO\n", i);
            break;
        }
    }

    if(videoindex == -1){
        fprintf(stderr, "Didn't find a video stream.\n");
        return -1;
    }

    pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec == NULL){
        printf("Codec not found.\n");
        return -1;
    }
    if(avcodec_open2(pCodecCtx, pCodec,NULL)<0){
        printf("Could not open codec.\n");
        return -1;
    }

    screen_w = pCodecCtx->width;
    screen_h = pCodecCtx->height;

    packet=(AVPacket *)av_malloc(sizeof(AVPacket));
    //Output Information-----------------------------
    printf("------------- File Information ------------------\n");
    av_dump_format(pFormatCtx, 0, argv[1], 0);
    printf("-------------------------------------------------\n");

    record_h264 = fopen(argv[2], "wb");

    AVBitStreamFilterContext* bsfc = av_bitstream_filter_init("h264_mp4toannexb");    

 	while(av_read_frame(pFormatCtx, packet) >= 0){

        if(packet->stream_index == videoindex){

    		av_bitstream_filter_filter(bsfc, pCodecCtx, NULL, &packet->data, &packet->size, packet->data, packet->size, 0);  
            write_ret = fwrite(packet->data, packet->size, 1, record_h264);
            if(write_ret <= 0)
            {
            	printf("fwrite error.");
            	break;
            }
            printf("one frame write_bit:%d\n", write_ret);
        }

        av_free_packet(packet);
    }

    av_bitstream_filter_close(bsfc);  

    printf("file parse finish.\n");

    avformat_close_input(&pFormatCtx);
    avcodec_close(pCodecCtx);

    fclose(record_h264);

	return 0;
}