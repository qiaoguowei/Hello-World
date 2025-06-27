#include <thrift/server/TNonblockingServer.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/async/TAsyncProtocolProcessor.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::async;

// 1. 定义异步服务处理器（需继承自 TAsyncProcessor）
class MyAsyncServiceHandler : public MyAsyncServiceIf {
public:
    void asyncMethod(std::function<void()> callback) override {
        // 异步方法实现（例如通过线程池处理）
        std::thread([callback] {
            // 模拟耗时操作
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            callback(); // 完成时触发回调
        }).detach();
    }
};

int main() {
    // 2. 创建协议工厂
    std::shared_ptr<TBinaryProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    // 3. 创建异步处理器
    std::shared_ptr<MyAsyncServiceHandler> handler(new MyAsyncServiceHandler());
    std::shared_ptr<MyAsyncServiceProcessor> processor(new MyAsyncServiceProcessor(handler));

    // 4. 创建异步协议处理器
    std::shared_ptr<TAsyncProtocolProcessor> asyncProtocolProcessor(
        new TAsyncProtocolProcessor(processor, protocolFactory)
    );

    // 5. 配置传输层
    std::shared_ptr<TTransportFactory> transportFactory(new TFramedTransportFactory());

    // 6. 创建非阻塞服务器
    TNonblockingServer server(
        asyncProtocolProcessor, // 关键：注入异步协议处理器
        transportFactory,
        9090 // 端口
    );

    // 7. 配置线程模型
    server.setNumIOThreads(4);      // IO 线程数（通常等于 CPU 核心数）
    server.setTaskExpireTime(5000); // 任务超时时间（毫秒）

    server.serve(); // 启动服务
    return 0;
}
