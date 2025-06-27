#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <vector>
#include <time.h>
#include <boost/smart_ptr.hpp>


enum OperationType  
{
	OT_NONE = 0,
	OT_MARK = 1,
	OT_UNMARK = 2,
	OT_UPDATE = 3,
	OT_END = 255
};

struct FileOPLogMetaInfo
{
	uint64_t revision_id;
	time_t op_time;
	std::string file_uuid;
	std::string operator_uuid;
	std::string user_uuid;
	std::string label_uuid;
	OperationType operation;
	std::string op_hash;
	uint16_t ds_id;
	std::string import_file_path;

	std::string refer_hash; // elma use it for resolve conflict.
	int syn_status; // elma use it for resolve conflict.

	FileOPLogMetaInfo() : revision_id(0), ds_id(0), syn_status(0) {}

	Json::Value toJson() const
	{
		Json::Value root;
		root["revision_id"] = static_cast<Json::Value::UInt64>(revision_id);
		root["time_stamp"] = static_cast<Json::Value::UInt64>(op_time);
		root["operator_uuid"] = operator_uuid;
		root["user_uuid"] = user_uuid;
		root["op_type"] = (int)operation;
		root["file_uuid"] = file_uuid;
		root["op_hash"] = op_hash;
		return root;
	}

	std::string toString() const
	{
		return toJson().toStyledString();
	}
};


typedef boost::shared_ptr<FileOPLogMetaInfo> OplogPtr;

struct SyncOpLogResult
{
	uint32_t error_code = 0;
	std::string message;
	time_t last_rollup_time;
	std::vector<OplogPtr> op_logs;
	std::string label_uuid;

	Json::Value toJson() const
	{
		Json::Value root;
		root["err_code"] = error_code;
		root["err_desc"] = message;
		root["last_rollup_time"] = static_cast<Json::Value::UInt64>(last_rollup_time);
		Json::Value node_oplogs;
		for(auto &x: op_logs)
		{
			Json::Value tmp = x->toJson();
			node_oplogs.append(tmp);
		}
		root["oplogs"] = node_oplogs;
		return root;
	}

	std::string toString() const
	{
		//std::cout << toJson().toStyledString() << std::endl;
		return toJson().toStyledString();
	}
};

int main()
{
	SyncOpLogResult so;
	OplogPtr op(new FileOPLogMetaInfo());
	so.op_logs.push_back(op);

	std::cout << so.toString() << std::endl;
}







