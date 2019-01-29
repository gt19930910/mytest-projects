/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */





/***
 *   download src url:  http://log4cpp.sourceforge.net/#propfile
 *
 *
 *   use log4cpp:
 *                      1. ./configure
 *                      2. make
 *                      3. make install
 *                      4. copy include & lib to your project
 *
 *
 *   write log4cpp.property


    # property configurator test file

    log4cpp.rootCategory=DEBUG, rootAppender
    log4cpp.category.sub1=DEBUG, A1

    log4cpp.appender.rootAppender=RollingFileAppender
    log4cpp.appender.rootAppender.fileName=/tmp/sink.log
    log4cpp.appender.rootAppender.maxFileSize=1024*1024*100
    log4cpp.appender.rootAppender.maxBackupIndex=1
    log4cpp.appender.rootAppender.layout=PatternLayout
    log4cpp.appender.rootAppender.layout.ConversionPattern=%d [%p] - %m%n


    log4cpp.appender.A1=RollingFileAppender
    log4cpp.appender.A1.fileName=/tmp/sink-err.log
    log4cpp.appender.A1.maxFileSize=1024*1024*100
    log4cpp.appender.A1.maxBackupIndex=1
    log4cpp.appender.A1.threshold=ERROR
    log4cpp.appender.A1.layout=PatternLayout
    log4cpp.appender.A1.layout.ConversionPattern=%d [%p] - %m%n


*/





#include <stdio.h>

#include <log4cpp/Portability.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/NDC.hh>
#include <log4cpp/PatternLayout.hh>

#include <log4cpp/PropertyConfigurator.hh>

int main(int arg0,char** arg1){
   
    std::string initFileName = "../log4cpp.property";
    try{
        log4cpp::PropertyConfigurator::configure(initFileName);
    } catch(log4cpp::ConfigureFailure& f) {
        std::cout << "Configure Problem " << f.what() << std::endl;
        return -1;
    }
    log4cpp::Category& root = log4cpp::Category::getRoot();
    log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));

    root.debug("root debug");
    root.info("root info");
    root.warn("root warn");
    root.error("root error");

    sub1.debug("sub1 debug");
    sub1.info("sub1 debug");
    sub1.warn("sub1 warn");
    sub1.error("sub1 error");



   return 0;
}
