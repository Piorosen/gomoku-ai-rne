#pragma once
#include "core.h"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <spdlog/spdlog.h>

#include <string>
#include <fstream>
#include <sstream>

namespace core
{
    class jsonManager
    {
    private:
        std::vector<std::string> split(std::string input, char delimiter)
        {
            std::vector<std::string> answer;
            std::stringstream ss(input);
            std::string temp;

            while (std::getline(ss, temp, delimiter))
            {
                answer.push_back(temp);
            }

            return answer;
        }

        rapidjson::Value convertNodeToValue(core::node node, rapidjson::Document::AllocatorType &allocator)
        {
            rapidjson::Value obj(rapidjson::kObjectType);
            rapidjson::Value p(rapidjson::kArrayType);

            obj.AddMember("score", node.score, allocator);
            obj.AddMember("pt", node.point.x * 100 + node.point.y, allocator);

            for (auto &item : node.next)
            {
                p.PushBack(convertNodeToValue(item, allocator), allocator);
            }

            obj.AddMember("node", p, allocator);

            return obj;
        }

    public:
        void newJson(std::string path)
        {
        }

        void saveJson(std::string path)
        {
            core::node rootNode = core::ai::shared->root;
            std::ofstream f(path);
            rapidjson::Document document;
            document.SetArray();

            rapidjson::Document::AllocatorType &allocator = document.GetAllocator();

            for (auto &item : rootNode.next)
            {
                document.PushBack(convertNodeToValue(item, allocator), allocator);
            }

            rapidjson::StringBuffer strbuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
            document.Accept(writer);
            f << strbuf.GetString();

            f.close();
        }

        void reLoad(std::string path, double discountRate = 0.5)
        {
            std::ifstream f(path);

            std::ostringstream ss;
            ss << f.rdbuf();
            std::string str = ss.str();

            f.close();

            rapidjson::Document document;
            document.Parse(str.c_str());

            if (document.HasParseError())
            {
                spdlog::info("core : pre learner load fail [{}]", path);
            }

            int dataSequence = 0;
            for (auto &item : document.GetArray())
            {
                if (std::strcmp(item["winby"].GetString(), "resign") != 0)
                {
                    continue;
                }

                if (dataSequence % 1000 == 0)
                {
                    spdlog::info("load data : [{}]", dataSequence);
                }
                std::string str = item["board"].GetString();
                auto list = split(str, ',');
                core::sqeuence seq;

                for (auto &li : list)
                {
                    core::point pt = {li[0] - 'a', atoi(&li[1])};
                    seq.push_back(pt);
                }
                auto r = std::strcmp(item["winner"].GetString(), "black") == 0;
                core::ai::shared->appendAI(seq, (core::color)r, discountRate);

                dataSequence++;
            }
        }
    };

}