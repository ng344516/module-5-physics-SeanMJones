#pragma once
#include "NetMsg.h"
#include "Mat4.h"
#include <Vector.h>

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
  class PhysxNetMsg : public NetMsg {
    public:
        NetMsgMacroDeclaration(PhysxNetMsg);

        PhysxNetMsg();
        virtual ~PhysxNetMsg();
        virtual bool toStream(NetMessengerStreamBuffer& os) const;
        virtual bool fromStream(NetMessengerStreamBuffer& is);
        virtual void onMessageArrived();
        virtual std::string toString() const;

        Mat4 pose;
        Vector pos;
        int index;

    };

} //namespace Aftr

#endif
