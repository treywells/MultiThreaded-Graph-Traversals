#pragma once

#pragma pack(push,1)
class CommandCC {
public:
    UCHAR command : 2; // lower 2 bits
    UCHAR planet : 6; // remaining 6 bits
    DWORD cave; // which cave
    USHORT robots; // how many robots

};

class ResponseCC {
public:
    DWORD status;
    char msg[64];
};

class CommandRobot {
public:
    DWORD command;
    UINT64 room; // unsigned __int64
};

class ResponseRobot {
public:
    DWORD status;
    char msg[64];
};

class NodeTuple64 {
public:
    UINT64 node;
    float intensity;
};
#pragma pack(pop)
