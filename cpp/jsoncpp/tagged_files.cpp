#include <iostream>
#include <jsoncpp/json/json.h>
#include <string>

using namespace std;


struct FileRecordMetaInfo
{
	std::string file_uuid;
	std::string label_uuid;
	std::string label_name;
	std::string user_name;
	std::string user_uuid;     
	std::string operator_uuid;
	std::string file_path;
	std::string file_name;
	uint16_t ds_id;
	int true_type;
	std::string endpoint_fqdn;//endpoint_name
	std::string endpoint_uuid;
	std::string endpoint_ip;
	int64_t last_op_time;
	size_t file_size;
	OperationType operation;
	std::string file_md5_hash;
	std::string last_op_hash;
	size_t similarity_code_count;
	double similarity_dilution_coefficient;
	int marker_type = 0;
	std::string marker_name = "N/A";
	std::string file_meta;
	char * file_codes = NULL;
	size_t file_codes_len = 0;
	FileCodes file_codes_origin;

	~FileRecordMetaInfo()
	{
		if(file_codes != NULL)
		{
			free(file_codes);
			file_codes = NULL;
			file_codes_len = 0;
		}
	}

	Json::Value toJson() const
	{
		Json::Value root;
		root["file_uuid"] = file_uuid;
		root["user_name"] = user_name;
		root["user_uuid"] = user_uuid;
		root["tag_uuid"] = label_uuid;
		root["tag_name"] = label_name;
		root["op_type"] = operation;
		root["last_op_hash"] = last_op_hash;
		root["last_op_time"] = (Json::Value::UInt64)last_op_time;
		root["file_name"] = file_name;
		root["file_path"] = file_path;
		root["true_type"] = true_type;
		root["endpoint_fqdn"] = endpoint_fqdn;
		root["endpoint_uuid"] = endpoint_uuid;
		root["endpoint_ip"] = endpoint_ip;
		root["file_size"] = (Json::Value::UInt64)file_size;
		root["file_md5_hash"] = file_md5_hash;

		root["marker_type"] = marker_type;
		root["marker_name"] = marker_name;

		//metadata
		Json::Value node_meta_data;
		if(!jsonlize(file_meta, node_meta_data))       
		{
			SG_WARN("file_meta can't be jsonlized");
		}
		root["datasource_id"] = node_meta_data["datasource_id"];

		//file_codes.
		Json::Value node_file_codes;
		node_file_codes["metadata"] = node_meta_data;
		node_file_codes["signatureMode"] = (Json::Value::UInt64)file_codes_origin.m_signatureMode;


		unstructured_precise_signature
			Json::Value node_us_p_s;
		node_us_p_s["binary_code"] = (Json::Value::UInt64)file_codes_origin.m_preciseSignature.mBinaryCode;
		node_us_p_s["short_binary_code"] = (Json::Value::UInt64)file_codes_origin.m_preciseSignature.mShortBinaryCode;
		node_us_p_s["texture_code"] = (Json::Value::UInt64)file_codes_origin.m_preciseSignature.mTextureCode;
		node_file_codes["unstructured_precise_signature"] = node_us_p_s;

		//unstructured_similarity_signature
		Json::Value node_us_s_s;
		//----similarity_codes
		Json::Value node_similarity_codes(Json::arrayValue);
		for(auto &x: file_codes_origin.m_similaritySignature.mSimilarityCodes)
		{
			node_similarity_codes.append((Json::Value::UInt64)x);
		}
		node_us_s_s["similarity_codes"] = node_similarity_codes;

		//-----second_similarity_codes
		Json::Value node_second_similarity_codes(Json::arrayValue);
		for(auto &x:file_codes_origin.m_similaritySignature.mSecondarySimilarityCodes) 
		{
			node_second_similarity_codes.append((Json::Value::UInt64)x);
		}
		node_us_s_s["second_similarity_codes"] = node_second_similarity_codes;

		node_file_codes["unstructured_similarity_signature"] = node_us_s_s;
		root["file_codes"] = node_file_codes;

		return root;
	}
};

typedef boost::shared_ptr<FileRecordMetaInfo> TaggedFilePtr;

struct GetTaggedFilesResult
{
	uint32_t error_code = 0;
	std::string message;
	std::vector<TaggedFilePtr> files;

	Json::Value toJson() const
	{
		Json::Value root;
		root["err_code"] = error_code;
		root["err_desc"] = message;
		Json::Value node_tagged_files;

		for(auto &x: files)
		{
			x->deserialize();
			Json::Value tmp = x->toJson();
			node_tagged_files.append(tmp);
		}

		root["tagged_files"] = node_tagged_files;
		return root;
	}

	std::string toString() const
	{
		cout << toJson().toStyledString() << endl;
		return toJson().toStyledString();                                                                              
	}
};


int main()
{
}
