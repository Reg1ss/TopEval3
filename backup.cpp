//
// Created by zhoub on 18-8-30.
//
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tinyxml.h"
#include "tinystr.h"
#include <iostream>
#include <thread>
#include <GPUCore/IGPUDeviceManager.h>
#include "ObjectDetectionFactory.h"
#include "TopObjectFeature/ObjectFeatureFactory.h"
#include "TopObjectClassification/ObjectClassificationFactory.h"
#include "TopObjectClassification/SyncObjectClassificationFactory.h"
#include "TopObstacle/ObstacleClassFactory.h"
#include <cuda_runtime_api.h>
#include <gflags/gflags.h>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <string>


using namespace tpv;
std::mutex LOCK;


void testDetectionModules(std::string inputPath, std::string outputPath, std::string id, std::shared_ptr<ObjectDetection> AlgoDet,int model);
void write2Xml(std::string outputPath, std::string id, std::vector<ObjectDetectionResult> res_v);
void write2Xml_score(std::string outputPath, std::string id, std::vector<ObjectDetectionResult> res_v);
std::shared_ptr<ObjectDetection> getAlgoDet(std::string modelPath);
char *itoa(int src);


int main(int argc, char *argv[]) {
    std::string id;
    std::string folderID;
//    test singal pics
//    testDetectionModules("/home/kuangrx/P0009/0009", "/home/kuangrx/P0009", "000000016");

//    testsingal folder pics
    std::string modelPath = "/home/kuangrx/TopTest/v0.6/TopHighwayDetection.dat";
    std::shared_ptr<ObjectDetection> AlgoDet = getAlgoDet(modelPath);
    std::string inputPath = "/home/kuangrx/frames/0002";
    std::string outputPath = "/home/kuangrx/xmls/0002_score";
    int model = 2;
//    int jumpID = 0;
//    for (int j = 40; j < 2091; ++j) {
//        if (j < 10) {
//            id = "00000000" + std::to_string(j);
//            std::string path = inputPath + "/" + id + ".jpg";
//            if (!access(path.data(), F_OK) == 0) {
//                j++;
//                jumpID++;
//                std::cout << "Jump : " << jumpID << std::endl;
//            }
//            std::cout << "objectID : " << id << std::endl;
//        }
//        if (9 < j < 100) {
//            id = "0000000" + std::to_string(j);
//            std::string path = inputPath + "/" + id + ".jpg";
//            if (!access(path.data(), F_OK) == 0) {
//                j++;
//                jumpID++;
//                std::cout << "Jump : " << jumpID << std::endl;
//            }
//            std::cout << "objectID : " << id << std::endl;
//        }
//        if (99 < j < 1000) {
//            id = "000000" + std::to_string(j);
//            std::string path = inputPath + "/" + id + ".jpg";
//            if (!access(path.data(), F_OK) == 0) {
//                j++;
//                jumpID++;
//                std::cout << "Jump : " << jumpID << std::endl;
//            }
//            std::cout << "objectID : " << id << std::endl;
//        }
//        if (j > 999) {
//            id = "00000" + std::to_string(j);
//            std::string path = inputPath + "/" + id + ".jpg";
//            if (!access(path.data(), F_OK) == 0) {
//                j++;
//                jumpID++;
//                std::cout << "Jump : " << jumpID << std::endl;
//            }
//            std::cout << "objectID : " << id << std::endl;
//        }
//        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//    }

    for (int j = 1; j < 300; j++) {
        if (j < 10) {
            id = "00000000" + std::to_string(j);
            std::string path = inputPath + "/" + id + ".jpg";
            if (access(path.data(), F_OK) == 0) {
                std::cout << "objectID : " << id << std::endl;
                testDetectionModules(inputPath, outputPath, id, AlgoDet, model);
            }
        }
        if (9 < j < 100) {
            id = "0000000" + std::to_string(j);
            std::string path = inputPath + "/" + id + ".jpg";
            if (access(path.data(), F_OK) == 0) {
                std::cout << "objectID : " << id << std::endl;
                testDetectionModules(inputPath, outputPath, id, AlgoDet, model);
            }
        }
        if (99 < j < 1000) {
            id = "000000" + std::to_string(j);
            std::string path = inputPath + "/" + id + ".jpg";
            if (access(path.data(), F_OK) == 0) {
                std::cout << "objectID : " << id << std::endl;
                testDetectionModules(inputPath, outputPath, id, AlgoDet, model);
            }
        }
        if (j > 999) {
            id = "00000" + std::to_string(j);
            std::string path = inputPath + "/" + id + ".jpg";
            if (access(path.data(), F_OK) == 0) {
                std::cout << "objectID : " << id << std::endl;
                testDetectionModules(inputPath, outputPath, id, AlgoDet, model);
            }
        }
    }
}
//    test testFolder pics
//    std::string inputPath = "/home/kuangrx/TopEval/testImage";
//    std::string outputPath = "/home/kuangrx/TopEval/testXml";
//    for (int j = 17; j < 260; ++j) {
//        id = "0_" + std::to_string(j);
//        std::string path = inputPath + "/" + id + ".jpg";
//        if (!access(path.data(), F_OK) == 0) {
//
//        }else{
//            testDetectionModules(inputPath, outputPath, id, AlgoDet);
//        }
//    }

//  algoTest
//    std::string modelPath = "/home/kuangrx/TopHighwayDetection.dat";
//    std::shared_ptr<ObjectDetection> AlgoDet = getAlgoDet(modelPath);
//    for (int i = 34; i < 53; i++) {
//        if (i > 26) {
//            std::string inputPathO = "/home/kuangrx/framesTunnel/";
//            std::string outputPathO = "/home/kuangrx/xmlsTunnel/";
//            std::string inputPath;
//            std::string outputPath;
//
//            if ((i - 26) < 10) {
//                inputPath = inputPathO + "000" + std::to_string(i - 26);
//                outputPath = outputPathO + "000" + std::to_string(i - 26);
//            } else {
//                inputPath = inputPathO + "00" + std::to_string(i - 26);
//                outputPath = outputPathO + "00" + std::to_string(i - 26);
//            }
//
//            for (int j = 1; j < 1500; j++) {
//                if (j < 10) {
//                    id = "00000000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                if (9 < j < 100) {
//                    id = "0000000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                if (99 < j < 1000) {
//                    id = "000000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                if (j > 999) {
//                    id = "00000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                std::cout << "fileCount : " << j << std::endl;
//                std::cout << "folderCount : " << i << std::endl;
//            }
//        } else {
//            std::string inputPathO = "/home/kuangrx/frames/";
//            std::string outputPathO = "/home/kuangrx/xmls/";
//            std::string inputPath;
//            std::string outputPath;
//
//            if (i < 10) {
//                inputPath = inputPathO + "000" + std::to_string(i);
//                outputPath = outputPathO + "000" + std::to_string(i);
//            } else {
//                inputPath = inputPathO + "00" + std::to_string(i);
//                outputPath = outputPathO + "00" + std::to_string(i);
//            }
//
//            for (int j = 1; j < 1500; j++) {
//                if (j < 10) {
//                    id = "00000000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                if (9 < j < 100) {
//                    id = "0000000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                if (99 < j < 1000) {
//                    id = "000000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                if (j > 999) {
//                    id = "00000" + std::to_string(j);
//                    std::string path = inputPath + "/" + id + ".jpg";
//                    if (access(path.data(), F_OK) == 0) {
//                        std::cout << "objectID : " << id << std::endl;
//                        testDetectionModules(inputPath, outputPath, id, AlgoDet);
//                    }
//                }
//                std::cout << "fileCount : " << j << std::endl;
//                std::cout << "folderCount : " << i << std::endl;
//            }
//        }
//    }
//}
//    std::string inputPath = "/home/kuangrx/TopEval/imageTest";
//    std::string outputPath = "/home/kuangrx/TopEval/xmlTest";
//    std::string id = "0_17";
//    testDetectionModules(inputPath,outputPath,id);



void testDetectionModules(std::string inputPath, std::string outputPath, std::string id, std::shared_ptr<ObjectDetection> AlgoDet, int model) {
    struct timeval tm_before, tm_after;

    cv::Mat testImg = cv::imread(inputPath + "/" + id + ".jpg");
    cv::cvtColor(testImg, testImg, CV_BGR2BGRA);
    cv::cuda::GpuMat gpuMat;
    gpuMat.upload(testImg);

    ObjectDetectionInitParams detectionInitParams;
    detectionInitParams.modelPath = "/home/kuangrx/TopHighwayDetection.dat";
//    auto AlgoDet = ObjectDetectionFactory().Create(detectionInitParams);

    LOCK.lock();
    AlgoDet->Init(detectionInitParams);
    LOCK.unlock();

    std::vector<ObjectDetectionResult> res_v;
    int num_a = 0;
    AlgoDet->Detect(gpuMat, res_v);
    num_a = res_v.size();

    gettimeofday(&tm_before, NULL);

    AlgoDet->Detect(gpuMat, res_v);
    if (res_v.size() != num_a) {
        std::cout << "error: same input ,diff results  : " << num_a << "vs " << res_v.size() << std::endl;
    }

    gettimeofday(&tm_after, NULL);
    printf(" a frame cost: %ld us\n",
           ((tm_after.tv_sec - tm_before.tv_sec) * 1000000 + (tm_after.tv_usec - tm_before.tv_usec)) / 1000);
    std::cout << "object num : " << res_v.size() << std::endl;

    char szLog[256];
    for (int i = 0; i < res_v.size(); i++) {

        if (res_v[i].className == "1")
            cv::rectangle(testImg, res_v[i].rect, cv::Scalar(0, 255, 0), 2);
        else if (res_v[i].className == "2") {
            cv::rectangle(testImg, res_v[i].rect, cv::Scalar(0, 0, 255), 2);
        }
        memset(szLog, 0, 256);
        sprintf(szLog, "%.3f", res_v[i].detectionScore);
        cv::putText(testImg, szLog, cvPoint(res_v[i].rect.x, res_v[i].rect.y), CV_FONT_HERSHEY_SIMPLEX, 0.4,
                    cvScalar(0, 255, 0));
//        std::cout<<"object name : "<<res_v[i].className<<std::endl;
//        std::cout<<"object coordinate : "<<res_v[i].rect<<std::endl;
//        std::cout<<"object x : "<<res_v[i].rect.x<<std::endl;
//        std::cout<<"object y : "<<res_v[i].rect.y<<std::endl;
    }

//    cv::imwrite("/home/kuangrx/P0009/000000016.jpg", testImg);
    std::cout << " detection test pass" << std::endl;

    if(model == 1){
        write2Xml(outputPath, id, res_v);
    }
    if(model == 2){
        write2Xml_score(outputPath, id, res_v);
    }
}

std::shared_ptr<ObjectDetection> getAlgoDet(std::string modelPath){
    ObjectDetectionInitParams detectionInitParams;
    detectionInitParams.modelPath = modelPath;
    auto AlgoDet = ObjectDetectionFactory().Create(detectionInitParams);
    return AlgoDet;
}

void write2Xml(std::string outputPath, std::string id, std::vector<ObjectDetectionResult> res_v) {
    //write to Xml
    std::string a = outputPath + "/" + id + ".xml";
    const char *xmlFile = a.data();
    TiXmlDocument doc;
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
    doc.LinkEndChild(decl);
    TiXmlElement *thirdLevel;
    TiXmlElement *firstLevel = new TiXmlElement("annotation");
    TiXmlElement *secondLevel = new TiXmlElement("folder");
    secondLevel->LinkEndChild(new TiXmlText("image"));
    firstLevel->LinkEndChild(secondLevel);
    secondLevel = new TiXmlElement("filename");
    std::string b = id + ".jpg";
    secondLevel->LinkEndChild(new TiXmlText(b.data()));//wait
    firstLevel->LinkEndChild(secondLevel);
    secondLevel = new TiXmlElement("path");
    secondLevel->LinkEndChild(new TiXmlText("...path"));//wait
    firstLevel->LinkEndChild(secondLevel);

    secondLevel = new TiXmlElement("source");
    thirdLevel = new TiXmlElement("database");
    thirdLevel->LinkEndChild(new TiXmlText("Unknown"));
    secondLevel->LinkEndChild(thirdLevel);
    firstLevel->LinkEndChild(secondLevel);

    secondLevel = new TiXmlElement("size");
    thirdLevel = new TiXmlElement("width");
    thirdLevel->LinkEndChild(new TiXmlText("1920"));
    secondLevel->LinkEndChild(thirdLevel);
    thirdLevel = new TiXmlElement("height");
    thirdLevel->LinkEndChild(new TiXmlText("1080"));
    secondLevel->LinkEndChild(thirdLevel);
    thirdLevel = new TiXmlElement("depth");
    thirdLevel->LinkEndChild(new TiXmlText("3"));
    secondLevel->LinkEndChild(thirdLevel);
    firstLevel->LinkEndChild(secondLevel);

    secondLevel = new TiXmlElement("segmented");
    secondLevel->LinkEndChild(new TiXmlText("0"));
    firstLevel->LinkEndChild(secondLevel);

    for (int j = 0; j < res_v.size(); j++) {
        secondLevel = new TiXmlElement("object");
        thirdLevel = new TiXmlElement("name");
        if (res_v[j].className == "1") {
            thirdLevel->LinkEndChild(new TiXmlText("car"));
            secondLevel->LinkEndChild(thirdLevel);
        } else if (res_v[j].className == "2") {
            thirdLevel->LinkEndChild(new TiXmlText("person"));
            secondLevel->LinkEndChild(thirdLevel);
        }
        thirdLevel = new TiXmlElement("pose");
        thirdLevel->LinkEndChild(new TiXmlText("Unspecified"));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("truncated");
        thirdLevel->LinkEndChild(new TiXmlText("0"));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("difficult");
        thirdLevel->LinkEndChild(new TiXmlText("0"));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("bndbox");
        TiXmlElement *forthLevel = new TiXmlElement("xmin");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.x)));
        thirdLevel->LinkEndChild(forthLevel);
        forthLevel = new TiXmlElement("ymin");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.y)));
        thirdLevel->LinkEndChild(forthLevel);
        forthLevel = new TiXmlElement("xmax");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.x + res_v[j].rect.width)));
        thirdLevel->LinkEndChild(forthLevel);
        forthLevel = new TiXmlElement("ymax");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.y + res_v[j].rect.height)));
        thirdLevel->LinkEndChild(forthLevel);

        secondLevel->LinkEndChild(thirdLevel);
        firstLevel->LinkEndChild(secondLevel);
    }
    doc.LinkEndChild(firstLevel);
    doc.SaveFile(xmlFile);
}

void write2Xml_score(std::string outputPath, std::string id, std::vector<ObjectDetectionResult> res_v) {
    //write to Xml
    std::string a = outputPath + "/" + id + ".xml";
    const char *xmlFile = a.data();
    TiXmlDocument doc;
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
    doc.LinkEndChild(decl);
    TiXmlElement *thirdLevel;
    TiXmlElement *firstLevel = new TiXmlElement("annotation");
    TiXmlElement *secondLevel = new TiXmlElement("folder");
    secondLevel->LinkEndChild(new TiXmlText("image"));
    firstLevel->LinkEndChild(secondLevel);
    secondLevel = new TiXmlElement("filename");
    std::string b = id + ".jpg";
    secondLevel->LinkEndChild(new TiXmlText(b.data()));//wait
    firstLevel->LinkEndChild(secondLevel);
    secondLevel = new TiXmlElement("path");
    secondLevel->LinkEndChild(new TiXmlText("...path"));//wait
    firstLevel->LinkEndChild(secondLevel);

    secondLevel = new TiXmlElement("source");
    thirdLevel = new TiXmlElement("database");
    thirdLevel->LinkEndChild(new TiXmlText("Unknown"));
    secondLevel->LinkEndChild(thirdLevel);
    firstLevel->LinkEndChild(secondLevel);

    secondLevel = new TiXmlElement("size");
    thirdLevel = new TiXmlElement("width");
    thirdLevel->LinkEndChild(new TiXmlText("1920"));
    secondLevel->LinkEndChild(thirdLevel);
    thirdLevel = new TiXmlElement("height");
    thirdLevel->LinkEndChild(new TiXmlText("1080"));
    secondLevel->LinkEndChild(thirdLevel);
    thirdLevel = new TiXmlElement("depth");
    thirdLevel->LinkEndChild(new TiXmlText("3"));
    secondLevel->LinkEndChild(thirdLevel);
    firstLevel->LinkEndChild(secondLevel);

    secondLevel = new TiXmlElement("segmented");
    secondLevel->LinkEndChild(new TiXmlText("0"));
    firstLevel->LinkEndChild(secondLevel);

    for (int j = 0; j < res_v.size(); j++) {
        secondLevel = new TiXmlElement("object");
        thirdLevel = new TiXmlElement("name");
        if (res_v[j].className == "1") {
            thirdLevel->LinkEndChild(new TiXmlText("car"));
            secondLevel->LinkEndChild(thirdLevel);
        } else if (res_v[j].className == "2") {
            thirdLevel->LinkEndChild(new TiXmlText("person"));
            secondLevel->LinkEndChild(thirdLevel);
        }
        thirdLevel = new TiXmlElement("pose");
        thirdLevel->LinkEndChild(new TiXmlText("Unspecified"));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("truncated");
        thirdLevel->LinkEndChild(new TiXmlText("0"));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("difficult");
        thirdLevel->LinkEndChild(new TiXmlText("0"));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("score");
        char score[100];
        sprintf(score, "%.3f", res_v[j].detectionScore);
        thirdLevel->LinkEndChild(new TiXmlText(score));
        secondLevel->LinkEndChild(thirdLevel);
        thirdLevel = new TiXmlElement("bndbox");
        TiXmlElement *forthLevel = new TiXmlElement("xmin");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.x)));
        thirdLevel->LinkEndChild(forthLevel);
        forthLevel = new TiXmlElement("ymin");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.y)));
        thirdLevel->LinkEndChild(forthLevel);
        forthLevel = new TiXmlElement("xmax");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.x + res_v[j].rect.width)));
        thirdLevel->LinkEndChild(forthLevel);
        forthLevel = new TiXmlElement("ymax");
        forthLevel->LinkEndChild(new TiXmlText(itoa(res_v[j].rect.y + res_v[j].rect.height)));
        thirdLevel->LinkEndChild(forthLevel);

        secondLevel->LinkEndChild(thirdLevel);
        firstLevel->LinkEndChild(secondLevel);
    }
    doc.LinkEndChild(firstLevel);
    doc.SaveFile(xmlFile);
}

char *itoa(int src) {
    int temp = -1;
    int tv = src > 0 ? src : -src;
    int length = 0;
    while ((tv = tv / 10) > 0) {
        length++;
    }
    length++;
    tv = src > 0 ? src : -src;
    char *des = (char *) malloc(sizeof(char) * (length + 1));
    memset(des, 0, length + 1);
    for (int i = 0; i < length; i++) {
        int v = 1;
        for (int j = length - i; j > 1; j--) {
            v = v * 10;
        }
        temp = tv / (v);
        des[i] = (temp + 48);//accii码0对应48
        if (temp == 0) {
            temp = 1;
        }
        tv = tv % (temp * v);
    }
    des[length] = '\0';
    if (src < 0) {
        char *nSrc = (char *) malloc((strlen(des) + 2) * sizeof(char));
        sprintf(nSrc, "-%s", des);
        free(des);
        des = nSrc;
    }
    return des;
}



