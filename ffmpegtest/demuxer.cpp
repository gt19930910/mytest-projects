/***
 *
 *   get h264/aac from mp4/flv...
 *
 *
 *   use ffmpeg-4.1
 *
 *   build ffmpeg:
 *                 1. download ffmpeg src
 *                 2. mkdir tmp
 *                 3. cd ffmpeg
 *                 4. ./configure --prefix=../tmp --enable-shared
 *                 5. make
 *                 6. make install
 *
 *  how to use this project:
 *
 *                 1. cd ffmpegtest/build
 *                 2. cmake ..
 *                 3. make
 *                 4. ./test ../media/source.200kbps.768x320.flv
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

extern "C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#include "libavutil/opt.h"
#include "libavutil/pixdesc.h"
}

int demuxer(int arg0,char** arg1){

    if (arg0 < 2) {
        printf("usage: %s input\n"
            "demux a media file with libavformat and libavcodec.\n"
             , arg1[0]);
        return 1;
    }

    const char *in_filename = arg1[1];
    const char *out_video_filename = "out_video.h264";
    const char *out_audio_filename = "out_audio.aac";

    int ret, i,video_index=-1,audio_index = -1;
    AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx_video = NULL,*ofmt_ctx_audio = NULL;

    av_register_all();

    if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
        printf( "Could not open input file.");
        goto end;
    }
    printf("avformat_open_input file:%s sucess\n",in_filename);

    if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
        printf( "Failed to retrieve input stream information");
        goto end;
    }
    printf("avformat_find_stream_info sucess stream num:%d\n",ifmt_ctx->nb_streams);

    //av_dump_format(ifmt_ctx, 0, in_filename, 0);
    //av_dump_format(ifmt_ctx, 1, in_filename, 0);

    // output
    avformat_alloc_output_context2(&ofmt_ctx_video, NULL, NULL, out_video_filename);
    if (!ofmt_ctx_video) {
        printf( "Could not create output context\n");
        ret = AVERROR_UNKNOWN;
        goto end;
    }
    avformat_alloc_output_context2(&ofmt_ctx_audio, NULL, NULL, out_audio_filename);
    if(!ofmt_ctx_audio) {
        printf( "Could not create output context\n");
        ret = AVERROR_UNKNOWN;
        goto end;
    }
    printf("avformat_alloc_output_context2 video\audio output context sucess\n");

    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        //根据输入流创建输出流（Create output AVStream according to input AVStream）
        AVStream *in_stream = ifmt_ctx->streams[i];

        AVFormatContext* ofmt_ctx = NULL;
        if( in_stream->codec->codec_type == AVMEDIA_TYPE_VIDEO ){
            ofmt_ctx = ofmt_ctx_video;
            video_index = i;
            printf("find video stream index:%d codec id:%d\n",i,in_stream->codec->codec_id);
        }else if(in_stream->codec->codec_type == AVMEDIA_TYPE_AUDIO){
            ofmt_ctx = ofmt_ctx_audio;
            audio_index = i;
            printf("find audio stream index:%d codec id:%d\n",i,in_stream->codec->codec_id);
        }else{
            continue;
        }

        av_dump_format(ifmt_ctx, i, in_filename, 0);

        AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
        if (!out_stream) {
            printf( "Failed allocating output stream\n");
            ret = AVERROR_UNKNOWN;
            goto end;
        }
        //复制AVCodecContext的设置（Copy the settings of AVCodecContext）
        ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
        if (ret < 0) {
            printf( "Failed to copy context from input to output stream codec context\n");
            goto end;
        }
        out_stream->codec->codec_tag = 0;
        if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
            out_stream->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

        // check if video==h264 and audio==aac
        if( (in_stream->codec->codec_type == AVMEDIA_TYPE_VIDEO ) && (!in_stream->codec->codec_id == AV_CODEC_ID_H264)){
            printf("!!!!!! error video is not h264\n");
            goto end;
        }
        if( (in_stream->codec->codec_type == AVMEDIA_TYPE_AUDIO ) && (!in_stream->codec->codec_id == AV_CODEC_ID_AAC)){
            printf("!!!!!! error audio is not aac\n");
            goto end;
        }

     }
     printf("AVFormatContext output context init ok\n");

     //输出一下格式------------------
     //av_dump_format(ofmt_ctx_video, 0, out_video_filename, 1);
     //av_dump_format(ofmt_ctx_audio, 0, out_audio_filename, 1);

     //打开输出文件（Open output file）
     if (ofmt_ctx_video && !(ofmt_ctx_video->oformat->flags & AVFMT_NOFILE)) {
         ret = avio_open(&ofmt_ctx_video->pb, out_video_filename, AVIO_FLAG_WRITE);
         if (ret < 0) {
             printf( "Could not open output file '%s'", out_video_filename);
             goto end;
         }
     }
     if (ofmt_ctx_audio && !(ofmt_ctx_audio->oformat->flags & AVFMT_NOFILE)) {
         ret = avio_open(&ofmt_ctx_audio->pb, out_audio_filename, AVIO_FLAG_WRITE);
         if (ret < 0) {
             printf( "Could not open output file '%s'", out_audio_filename);
             goto end;
         }
     }

     //写文件头（Write file header）
     ret = avformat_write_header(ofmt_ctx_video, NULL);
     if (ret < 0) {
         printf( "Error occurred when opening output file\n");
         goto end;
     }
     ret = avformat_write_header(ofmt_ctx_audio, NULL);
     if (ret < 0) {
         printf( "Error occurred when opening output file\n");
         goto end;
     }

    static AVBitStreamFilterContext* bsfc =  av_bitstream_filter_init("h264_mp4toannexb");

    AVPacket pkt;
    while (1) {
        static int packet_num = 0;
        //获取一个AVPacket（Get an AVPacket）
        ret = av_read_frame(ifmt_ctx, &pkt);
        if (ret < 0){
            printf("break av_read_frame num:%d\n",packet_num);
            break;
        }
        packet_num++;

        // printf("Write %8d frames to output file pts:%lld\n",frame_index,pkt.pts);
        AVFormatContext* ofmt_ctx = NULL;
        if(pkt.stream_index == video_index){
            ofmt_ctx = ofmt_ctx_video;
            if(bsfc){
                av_bitstream_filter_filter(bsfc, ofmt_ctx_video->streams[0]->codec, NULL, &pkt.data, &pkt.size, pkt.data, pkt.size,0);
            }
        }else if(pkt.stream_index == audio_index){
            ofmt_ctx = ofmt_ctx_audio;
        }
        //写入（Write）
        if(ofmt_ctx){
            pkt.stream_index = 0;
            ret = av_interleaved_write_frame(ofmt_ctx, &pkt);
            if (ret < 0) {
                printf( "Error muxing packet\n");
                break;
            }
        }
        av_free_packet(&pkt);
    }
    printf("write to file ok!!!\n");

    //写文件尾（Write file trailer）
    if(ofmt_ctx_video)
        av_write_trailer(ofmt_ctx_video);
    if(ofmt_ctx_audio)
        av_write_trailer(ofmt_ctx_audio);

end:
    avformat_close_input(&ifmt_ctx);
    if (ofmt_ctx_video && !(ofmt_ctx_video->oformat->flags & AVFMT_NOFILE))
        avio_close(ofmt_ctx_video->pb);
    if (ofmt_ctx_audio && !(ofmt_ctx_audio->oformat->flags & AVFMT_NOFILE))
        avio_close(ofmt_ctx_audio->pb);
    if(ofmt_ctx_video)
        avformat_free_context(ofmt_ctx_video);
    if(ofmt_ctx_audio)
        avformat_free_context(ofmt_ctx_audio);

    return 0;
}


