#pragma once

#include "NetMsg.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

    class NetworkingNetMsg : public NetMsg
    {
    public:
        NetMsgMacroDeclaration(NetworkingNetMsg);

        NetworkingNetMsg();
        virtual ~NetworkingNetMsg();
        virtual bool toStream(NetMessengerStreamBuffer& os) const;
        virtual bool fromStream(NetMessengerStreamBuffer& is);
        virtual void onMessageArrived();
        virtual std::string toString() const;

    protected:
        unsigned int id;
        Aftr::Vector pos;

    };

} //namespace Aftr

#endif