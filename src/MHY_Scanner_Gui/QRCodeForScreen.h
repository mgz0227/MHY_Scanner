﻿#pragma once

#include <functional>

#include <QMutex>
#include <QThread>

#include "Common.h"
#include "ConfigDate.h"
#include "Mihoyosdk.h"
#include "OfficialApi.h"

class QRCodeForScreen final :
    public QThread
{
    Q_OBJECT
public:
    QRCodeForScreen(QObject* parent);
    ~QRCodeForScreen();
    void setLoginInfo(const std::string& uid, const std::string& token);
    void setLoginInfo(const std::string& uid, const std::string& token, const std::string& name);
    void setServerType(const ServerType::Type& servertype);
    void continueLastLogin();
    void run();
    void stop();
signals:
    void loginResults(const ScanRet::Type ret);
    void loginConfirm(const GameType::Type gameType, bool b);

private:
    OfficialApi o;
    Mihoyosdk m;
    ConfigDate* m_config;
    void LoginOfficial();
    void LoginBH3BiliBili();
    std::atomic<bool> m_stop;
    std::string uid;
    std::string gameToken;
    std::string m_name;
    std::map<std::string_view, std::function<void()>> setGameType{
        { "8F3", [this]() { m_gametype = GameType::Type::Honkai3; } },
        { "9E&", [this]() { m_gametype = GameType::Type::Genshin; } },
        { "8F%", [this]() { m_gametype = GameType::Type::StarRail; } },
    };
    GameType::Type m_gametype = GameType::Type::UNKNOW;
    ServerType::Type servertype;
    ScanRet::Type ret = ScanRet::Type::UNKNOW;
    const int threadNumber = 1;
};