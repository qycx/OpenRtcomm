#include "stdio.h"
#include "thirdparty/libcurl/include/curl.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char* ptr = (char*)calloc(mem->size + realsize + 1, sizeof(char));
    if(!ptr) {
        printf("内存申请失败！\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}



int main()
{
    clock_t start, end;
    struct MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);  
    chunk.size = 0;
    curl_global_init(CURL_GLOBAL_ALL);
    start = clock();
    CURL* curl = curl_easy_init();
    if (curl)
    {
        const char* url = "https://223.70.139.221:2059/--auth-pre--/aaa/cert/random";

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);


        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        CURLcode curlCode = curl_easy_perform(curl);
        if (CURLE_OK != curlCode)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlCode));
        curl_easy_cleanup(curl);
        int http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        end = clock();
        printf("接口调用耗时:%f s\n", double(end - start) / CLOCKS_PER_SEC );
    }
    else
        printf("Something went wrong\n");
    curl_global_cleanup();
    free(chunk.memory);
    free(chunk);
    //system("pause");
    return 0;
}