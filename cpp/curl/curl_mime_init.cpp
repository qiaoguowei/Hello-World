#include <iostream>
#include <curl/curl.h>

/*
    curl_mime *curl_mime_init(CURL *easy_handle);

    curl_mime_init创建一个新的空mime结构句柄。这个mime结构可以随后使用mime API填充，然后在curl_easy_setopt调用中使用选项CURLOPT_MIMEPOST附加到一些简单句柄上，或者使用curl_mime_subparts作为多部分添加到另一个mime句柄的部分中。

    easy_handle用于部分分隔符随机化和错误报告。从7.87.0开始，它不需要是最终目标句柄。

    使用mime句柄是推荐的使用SMTP发布HTTP表单、格式化和发送多部分电子邮件或将此类电子邮件上传到IMAP服务器的方法。

    
    curl_mimepart *curl_mime_addpart(curl_mime *mime);

    `curl_mime_addpart()` 会创建一个新的空部分并将其附加到指定的 MIME 结构中，并返回该部分的句柄。返回的句柄可以随后使用 MIME API 中的函数进行填充。

    `mime` 是必须将新部分附加到其中的 MIME 结构的句柄。

    
    CURLcode curl_mime_data(curl_mimepart *part, const char *data, size_t datasize);

    Curl_mime_data从内存数据中设置mime部分的主体内容。


    Part是要分配内容的mime部分，使用curl_mime_addpart创建。


    Data指的是被这个函数复制的数据。在调用之后可以安全地重用存储。


    Datasize是数据点指向的字节数。它可以设置为CURL_ZERO_TERMINATED，以指示数据是一个以空结束的字符串。


    多次设置一个部件的内容是有效的:只有最后一次调用设置的值被保留。可以通过将data设置为NULL来取消部分内容的分配。


    设置大数据会消耗内存:在这种情况下可以考虑使用curl_mime_data_cb。

    
    CURLcode curl_mime_name(curl_mimepart *part, const char *name);

    `curl_mime_name` 设置 MIME 部分的名称。这是 HTTP 表单字段的命名方式。

    `part` 是分配名称的 MIME 部分的句柄。

    `name` 指向空终止的名称字符串。

    将名称字符串复制到部分中，因此在调用后可以安全地释放或重用相关存储。多次为部分设置名称是合法的：仅保留最后一次调用设置的值。可以通过将 `name` 设置为空指针来重置部分的名称。
*/

int main()
{
    CURL *easy = curl_easy_init();
    curl_mime *mime;
    curl_mimepart *part;

    /* Build an HTTP form with a single field named "data", */
    mime = curl_mime_init(easy);
    part = curl_mime_addpart(mime);
    curl_mime_data(part, "This is the field data", CURL_ZERO_TERMINATED);
    curl_mime_name(part, "data");

    part = curl_mime_addpart(mime);
    curl_mime_data(part, "This is the second field data", CURL_ZERO_TERMINATED);
    curl_mime_name(part, "second_data");

    /* Post and send it. */
    curl_easy_setopt(easy, CURLOPT_MIMEPOST, mime);
    curl_easy_setopt(easy, CURLOPT_URL, "http://172.22.37.100:9001");
    curl_easy_perform(easy);

    /* Clean-up. */
    curl_easy_cleanup(easy);
    curl_mime_free(mime);
}
