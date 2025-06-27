#include <iostream>
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <map>
#include <string>
#include <memory>

using namespace std;

bool make_x509_csr(const std::map<std::string, std::string>& entry_list, std::string& private_key, std::string& cert_csr)
{
    bool res = false;

    do
    {
        //生成 RSA 密钥，param1是模数比特数，param2是公钥指数 e，param3回调函数由用户实现，用于干预密钥生成过程中的一些运算，可为空，param4是回调函数的参数。
        RSA* rsa_key = RSA_generate_key(2048, RSA_F4, NULL, NULL);
        if (!rsa_key)
        {
            cerr << "RSA_generate_key failed." << endl;
            break;
        }
        //key
        {
            //mem类型的IO    内存
            std::unique_ptr<BIO, decltype(&BIO_free)> mem_key(BIO_new(BIO_s_mem()), BIO_free);
            if (!mem_key)
            {
                cerr << "BIO_new failed." << endl;
                break;
            }

            //PEM_write_XXXX/PEM_write_bio_XXXX 
            //将 XXXX 代表的信息类型写入到文件/bio 中。
            if (!PEM_write_bio_RSAPrivateKey(mem_key.get(), rsa_key, NULL, NULL, 0, NULL, NULL))
            {
                cerr << "PEM_write_bio_RSAPrivateKey failed." << endl;
                break;
            }

            char *data = NULL;
            int32_t len = BIO_get_mem_data(mem_key.get(), &data);
            private_key.assign(data, data + len);
        }

        //csr
        //该结构用来存放非对称密钥信息，可以是 RSA、DSA、DH 或 ECC 密钥。
        std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> evp_key(EVP_PKEY_new(), EVP_PKEY_free);
        if (!evp_key)
        {
            cerr << "EVP_PKEY_new failed." << endl;
            break;
        }

        //设置 EVP_PKEY 中的 RSA 密钥结构，使它代表该 RSA 密钥。
        EVP_PKEY_assign_RSA(evp_key.get(), rsa_key);

        std::unique_ptr<X509_REQ, decltype(&X509_REQ_free)> x509_req(X509_REQ_new(), X509_REQ_free);
        if (!x509_req)
        {
            cerr << "X509_REQ_new failed." << endl;
            break;
        }

        //设置版本号
        X509_REQ_set_version(x509_req.get(), 0);
        //设置公钥，EVP_PKEY *pkey参数就是生成好的公钥，可以通过RSA_generate_key()来生成
        X509_REQ_set_pubkey(x509_req.get(), evp_key.get());

        //获取证书请求的申请者信息。
        X509_NAME *name = X509_REQ_get_subject_name(x509_req.get());
        if (NULL == name)
        {
            cerr << "X509_REQ_get_subject_name failed." << endl;
            break;
        }

        for (const auto& iter : entry_list)
        {
            //创建一个字符串内容项。
            X509_NAME_add_entry_by_txt(name, iter.first.c_str(), MBSTRING_ASC,
                    reinterpret_cast<unsigned char *>(const_cast<char *>(iter.second.c_str())), -1, -1, 0);
        }

        //对证书请求结构进行签名。
        X509_REQ_sign(x509_req.get(), evp_key.get(), EVP_sha256());

        {
            std::unique_ptr<BIO, decltype(&BIO_free)> mem_cert(BIO_new(BIO_s_mem()), BIO_free);
            if (!mem_cert)
            {
                cerr << "BIO_new failed." << endl;
                break;
            }

            //将 XXXX 代表的信息类型写入到文件/bio 中。  PEM_write_XXXX/PEM_write_bio_XXXX 
            if (!PEM_write_bio_X509_REQ(mem_cert.get(), x509_req.get()))
            {
                cerr << "PEM_write_bio_X509_REQ failed." << endl;
                break;
            }

            char *data = NULL;
            int32_t len = BIO_get_mem_data(mem_cert.get(), &data);
            cert_csr.assign(data, data + len);
        }

        res = true;
    } while(0);

    return res;
}

int main()
{
    std::map<std::string, std::string> entry_list{
            {"C", "CN"},
            {"ST", "Beijing"},
            {"L", "DaXing"},
            {"OU", "SKYGUARD"},
            {"O", "SKYGUARD"},
            {"CN", "a73de055-93d4-4223-9157-4129bb104850"}
    };

    string private_key;
    string cert_csr;
    make_x509_csr(entry_list, private_key, cert_csr);
    cout << private_key << endl;
    cout << cert_csr << endl;
}



















