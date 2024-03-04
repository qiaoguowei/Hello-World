#include <iostream>
#include <string>

using namespace std;

struct ProtocolFlags {
    enum type {
        PF_ASYNC = 1,
        PF_VERBOSE = 2,
        PF_MONITOR = 4,
        PF_SIMPLE_MATCHING = 8,
        PF_DELETE_FILE_BY_SERVER = 16,
        PF_MONITOR_WAITING = 32,
        PF_AGENT_ACTION_CONFIRM = 64,
        PF_DIAGNOSE = 128,
        PF_DONOT_MAP_FILE = 256
    };
};


int main()
{
    int32_t proto_flags = 0;
    proto_flags |= ProtocolFlags::PF_ASYNC | ProtocolFlags::PF_VERBOSE;

    cout << static_cast<ProtocolFlags::type>(proto_flags) << endl;
}
