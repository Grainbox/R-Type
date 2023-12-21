# ReceiveUDP Component Documentation

## Overview
The `ReceiveUDP` component is a part of the B-CPP-500-REN-5-2-rtype project. It is designed to handle UDP communication in a component-based architecture. This component utilizes Boost Serialization for efficient data serialization and deserialization.

## File: `ReceiveUDP.hpp`
Located in `engine/include/components`, the `ReceiveUDP.hpp` file defines the `ReceiveUDP` class.

## IMPORTANT: Every components MUST have a default constructor (it can do nothing)

### Class Definition
```cpp
#ifndef RECEIVEUDP_HPP_
#define RECEIVEUDP_HPP_

#include <boost/serialization/serialization.hpp>
#include <cstddef>

class ReceiveUDP {
    public:
        ReceiveUDP() {};
        ReceiveUDP(size_t script_id) : script_id(script_id) {};

        size_t script_id;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & script_id;
        }

        friend class boost::serialization::access;
    protected:
    private:
};

#endif /* !RECEIVEUDP_HPP_ */
```

## Integration
### Component Inclusion
Include `ReceiveUDP` in `ComponentIncluder.hpp`:
```cpp
#include "ReceiveUDP.hpp"
```

### EntityComponents Structure
In `Communication_Structures.hpp`, integrate `ReceiveUDP` into the `EntityComponents` struct for serialization:
```cpp
struct EntityComponents {
    size_t entity_id;
    // Other components...
    boost::optional<ReceiveUDP> receiveUdp;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & entity_id;
        // Serialization of other components...
        ar & receiveUdp;
    }
};
```

## Usage
To use the `ReceiveUDP` component, create an instance with a unique script identifier. This component is then serialized/deserialized using Boost Serialization as part of the entity-component system.

## Note
Ensure that all types used within `ReceiveUDP` are serializable with Boost. If a type is not directly serializable, use an identifier or an alternative serializable type.
