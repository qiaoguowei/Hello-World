#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
/*
4. 代码解释

    创建 TBinaryProtocolFactory：在 serializeExampleStruct 和 deserializeExampleStruct 函数中，首先创建了 TBinaryProtocolFactory 对象。
    使用工厂创建 TBinaryProtocol：调用 protocolFactory.getProtocol(transport) 方法，传入传输对象，创建一个 TBinaryProtocol 对象。
    序列化和反序列化：在 serializeExampleStruct 函数中，使用 TBinaryProtocol 对象将 ExampleStruct 结构体序列化为二进制数据；在 deserializeExampleStruct 函数中，将二进制数据反序列化为 ExampleStruct 结构体。
    主函数：创建一个示例结构体，进行序列化和反序列化操作，并输出反序列化结果。

 */

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

// 假设我们有一个简单的结构体
struct ExampleStruct {
    int32_t id;
    std::string name;
};

// 自定义序列化函数
void serializeExampleStruct(ExampleStruct& example, std::shared_ptr<TTransport> transport) {
    // 创建 TBinaryProtocolFactory
    TBinaryProtocolFactory protocolFactory;
    // 使用工厂创建 TBinaryProtocol 对象
    std::shared_ptr<TProtocol> protocol = protocolFactory.getProtocol(transport);

    // 开始序列化
    protocol->writeStructBegin("ExampleStruct");

    protocol->writeFieldBegin("id", TType::T_I32, 1);
    protocol->writeI32(example.id);
    protocol->writeFieldEnd();

    protocol->writeFieldBegin("name", TType::T_STRING, 2);
    protocol->writeString(example.name);
    protocol->writeFieldEnd();

    protocol->writeFieldStop();
    protocol->writeStructEnd();
}

// 自定义反序列化函数
void deserializeExampleStruct(ExampleStruct& example, std::shared_ptr<TTransport> transport) {
    // 创建 TBinaryProtocolFactory
    TBinaryProtocolFactory protocolFactory;
    // 使用工厂创建 TBinaryProtocol 对象
    std::shared_ptr<TProtocol> protocol = protocolFactory.getProtocol(transport);

    // 开始反序列化
    protocol->readStructBegin();
    while (true) {
        TField field;
        protocol->readFieldBegin(field);
        if (field.type == TType::T_STOP) {
            break;
        }
        switch (field.id) {
            case 1:
                if (field.type == TType::T_I32) {
                    protocol->readI32(example.id);
                }
                break;
            case 2:
                if (field.type == TType::T_STRING) {
                    protocol->readString(example.name);
                }
                break;
            default:
                protocol->skip(field.type);
                break;
        }
        protocol->readFieldEnd();
    }
    protocol->readStructEnd();
}

int main() {
    // 创建一个示例结构体
    ExampleStruct example;
    example.id = 1;
    example.name = "Test";

    // 创建传输对象
    std::shared_ptr<TTransport> transport(new TMemoryBuffer());

    // 序列化结构体
    serializeExampleStruct(example, transport);

    // 重置传输对象以便读取
    transport->resetBuffer();

    // 反序列化结构体
    ExampleStruct deserialized;
    deserializeExampleStruct(deserialized, transport);

    // 输出反序列化结果
    std::cout << "Deserialized ID: " << deserialized.id << std::endl;
    std::cout << "Deserialized Name: " << deserialized.name << std::endl;

    return 0;
}

