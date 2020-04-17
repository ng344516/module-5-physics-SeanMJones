#pragma once

#include "NetMsg.h"
#include <Vector.h>
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{

    class PlayerMovement : public NetMsg
    {
    public:
        NetMsgMacroDeclaration(PlayerMovement);

        PlayerMovement();
        virtual ~PlayerMovement();
        virtual bool toStream(NetMessengerStreamBuffer& os) const;
        virtual bool fromStream(NetMessengerStreamBuffer& is);
        virtual void onMessageArrived();
        virtual std::string toString() const;
        Vector ptranslation = Vector(0, 0, 0);
        Vector protation = Vector(0, 0, 0);
        Vector ltranslation = Vector(0, 0, 0);
        Vector lrotation = Vector(0,0,0);
        std::string usermsg = "Player1";

    protected:
        unsigned int id;

    };

} //namespace Aftr

#endif
