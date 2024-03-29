/*
 * @CopyRight:
 * FISCO-BCOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FISCO-BCOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FISCO-BCOS.  If not, see <http://www.gnu.org/licenses/>
 * (c) 2016-2018 fisco-dev contributors.
 */
/**
 * @brief : keycenter server
 * @author: jimmyshi
 * @date: 2018-12-04
 */
#pragma once
#include "AES.h"
#include "Common.h"
#include "Exceptions.h"
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <memory>
#include <string>

#define KCLOG(_OBV) std::cout << "[" << dev::utcTime() << "] [" #_OBV "] "

class BaseServer : public jsonrpc::AbstractServer<BaseServer>
{
public:
    BaseServer(jsonrpc::HttpServer& server) : jsonrpc::AbstractServer<BaseServer>(server)
    {
        this->bindAndAddMethod(jsonrpc::Procedure("sayHello", jsonrpc::PARAMS_BY_NAME,
                                   jsonrpc::JSON_STRING, "name", jsonrpc::JSON_STRING, NULL),
            &BaseServer::sayHello);

        this->bindAndAddMethod(jsonrpc::Procedure("decDataKey", jsonrpc::PARAMS_BY_POSITION,
                                   jsonrpc::JSON_OBJECT, "param1", jsonrpc::JSON_STRING, NULL),
            &BaseServer::decDataKey);

        this->bindAndAddMethod(jsonrpc::Procedure("encDataKey", jsonrpc::PARAMS_BY_POSITION,
                                   jsonrpc::JSON_OBJECT, "param1", jsonrpc::JSON_STRING, NULL),
            &BaseServer::encDataKey);
    }

    // method
    void decDataKey(const Json::Value& request, Json::Value& response);
    void encDataKey(const Json::Value& request, Json::Value& response);

    virtual std::string decryptDataKeyHex(const std::string& _cypherDataKey)
    {
        return std::string();
    }
    virtual std::string encryptDataKey(const std::string& _dataKey) { return std::string(); }

    void sayHello(const Json::Value& request, Json::Value& response)
    {
        response = "Hello: " + request["name"].asString();
    }
};

class KeyCenter : public BaseServer
{
public:
    KeyCenter(jsonrpc::HttpServer& _connector, const dev::bytes& _superKey)
      : BaseServer(_connector), m_superKey(_superKey){};

    ~KeyCenter()
    {
        this->StopListening();
        KCLOG(TRACE) << "keycenter exit." << std::endl;
    }

    virtual std::string decryptDataKeyHex(const std::string& _cypherDataKey) override;
    virtual std::string encryptDataKey(const std::string& _dataKey) override;

private:
    dev::bytes m_superKey;
};
