#include "Tool.h"

shared_ptr<Tool> g_pTool = make_shared<Tool>();

wstring s2ws(const string& s)
{
	int32 len;
	int32 slength = static_cast<int32>(s.length()) + 1;
	len = ::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	::MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring ret(buf);
	delete[] buf;
	return ret;
}

string ws2s(const wstring& s)
{
	int32 len;
	int32 slength = static_cast<int32>(s.length()) + 1;
	len = ::WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	string r(len, '\0');
	::WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
	return r;
}

wstring AbsolutePathToRelativePath(const wstring& szAbsolutePath)
{
	wstring szResourcesPath = L"..\\Resources\\";

	uint32 iSplitPoint = static_cast<uint32>(szAbsolutePath.find(L"Texture\\"));
	assert(iSplitPoint != wstring::npos);

	wstring szResultPath = szResourcesPath + szAbsolutePath.substr(iSplitPoint);

	return szResultPath;
}