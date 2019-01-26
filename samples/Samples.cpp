#include "CurlHelper.h"

#define LOCAL_URL "http://127.0.0.1:8081"
#define REMOTE_URL "http://111.230.238.128:8081"

#define UPLOAD "/upload"
#define SEOAREA_QUERY "/seoarea/query"

int main(int argc, char ** argv)
{
	CURLcode curlCode = CURLcode::CURLE_OK;
	curlCode = curl_http_startup();

	std::string strResult = "";
	pbytedata pbd = bytedata::startup();
	const char * pheaderdata = "Expect:";
	std::string url = std::string(LOCAL_URL) + SEOAREA_QUERY;
	std::map<std::string, std::string> sv = { { "data", AToUTF8("{\"seo_area\":\"东北\"}") } };
	curlCode = curl_http_form_execute(pbd, url.c_str(), true, pheaderdata, &sv);
	if (curlCode == CURLcode::CURLE_OK)
	{
		strResult = UTF8ToA(pbd->p);
	}

	pbd->clear();

	url = std::string(LOCAL_URL) + UPLOAD;
	std::map<std::string, std::string> file_sv = { { "photo", AToUTF8("D:/1.png") } };
	curlCode = curl_http_form_execute(pbd, url.c_str(), true, pheaderdata, &file_sv);
	if (curlCode == CURLcode::CURLE_OK)
	{
		strResult = UTF8ToA(pbd->p);
	}

	curl_http_cleanup();

	return 0;
}