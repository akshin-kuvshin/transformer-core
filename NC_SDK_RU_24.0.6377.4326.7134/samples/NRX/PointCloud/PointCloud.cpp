//
// Копирайт (С) 2019, ООО «Нанософт разработка». Все права защищены.
// 
// Данное программное обеспечение, все исключительные права на него, его
// документация и сопроводительные материалы принадлежат ООО «Нанософт разработка».
// Данное программное обеспечение может использоваться при разработке и входить
// в состав разработанных программных продуктов при соблюдении условий
// использования, оговоренных в «Лицензионном договоре присоединения
// на использование программы для ЭВМ «Платформа nanoCAD»».
// 
// Данное программное обеспечение защищено в соответствии с законодательством
// Российской Федерации об интеллектуальной собственности и международными
// правовыми актами.
// 
// Используя данное программное обеспечение,  его документацию и
// сопроводительные материалы вы соглашаетесь с условиями использования,
// указанными выше. 
//

#include "stdafx.h"
#include "resource.h"
#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <corecrt_wstdio.h>
#include "PointCloudBridge.h"
#include "PointCloudInsertion.h"
#include "VisualizationParams.h"
#include "Coloring.h"
#include "Clipping.h"


using namespace NPC_API;
using fileType = PointCloudBridge::_FileDataType;

void runPointCloudCmd();

extern "C" __declspec(dllexport) AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId)
{
    switch (msg)
    {
    case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
        acrxDynamicLinker->registerAppMDIAware(appId);

        acedRegCmds->addCommand(L"CLOUD_GROUP",
            L"_POINTCLOUD",
            L"POINTCLOUD",
            ACRX_CMD_TRANSPARENT,
            runPointCloudCmd);
        break;

    case AcRx::kUnloadAppMsg:
        acedRegCmds->removeGroup(L"CLOUD_GROUP");
        break;
    }
    return AcRx::kRetOK;
}

#define INP_KEYWORD     0
#define INP_ERROPTION  -1

class PromptKwd
{
private:
    HINSTANCE m_hinstanse;
    std::vector<AcString> m_options;
    AcString m_prompt;
    AcString m_kwd;

public:
    PromptKwd(int idPrompt, int idKwd)
        : m_hinstanse((HINSTANCE)This_GetInstance())
    {
        m_kwd = AcString(m_hinstanse, idKwd);
        if (!splittingString(m_options, m_kwd, L' ')) {
            m_kwd.setEmpty();
            return;
        }
        m_prompt = AcString(m_hinstanse, idPrompt) + _T(" [");
        int count = 0;
        for (auto item : m_options)
            m_prompt += item + (count++ == m_options.size() - 1 ? _T("]") : _T("/"));
    }
    PromptKwd() = delete;
    ~PromptKwd() = default;

    void addDefOption(int numOption) {
        numOption--;
        if (numOption >= m_kwd.length() || numOption < 0)
            return;
        m_prompt += AcString(_T(" <")) + m_options[numOption] + _T(">");
    }
    int operator()(const NCHAR* sOption) {
        for (int i = 0; i < (int)m_options.size(); ++i)
            if (m_options[i] == sOption)
                return INP_KEYWORD + i;
        return INP_ERROPTION;
    }
    bool isValid() const {
        return !(m_prompt.isEmpty() || m_kwd.isEmpty() || m_options.empty() || m_hinstanse == nullptr);
    }
    AcString getPathModule() const {
        AcString path;
        TCHAR pszFileName[MAX_PATH] = { _T("\0") };
        GetModuleFileName(m_hinstanse, pszFileName, MAX_PATH);
        path = pszFileName;
        path = path.substr(path.findRev(_T("\\")));
        return path;
    }
    AcString const& getPrompt() const { return m_prompt; }
    AcString const& getKwd() const { return m_kwd; }
    AcString getString(int id) const { return AcString(m_hinstanse, id); }
    HINSTANCE getInstance() const { return m_hinstanse; }

private:
    static void* This_GetInstance(void)
    {
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery(This_GetInstance, &mbi, sizeof(mbi));
        return mbi.AllocationBase;
    }
    bool splittingString(std::vector<AcString>& vList, AcString const& string, wchar_t symbol)
    {
        std::wstring str(string.kTCharPtr());
        if (str.empty())
            return false;
        auto iter = str.begin();
        while (iter != str.end())
        {
            std::wstring sTemp;
            auto left = std::find_if_not(iter, str.end(), [symbol](wchar_t _symbol)
                { return symbol == _symbol; });
            auto right = std::find_if_not(left, str.end(), [symbol](wchar_t _symbol)
                { return symbol != _symbol; });
            ptrdiff_t size = right - left;
            if (size >= INT32_MAX)
                return false;
            sTemp.resize(static_cast<int>(size));
            if(left != right)
                std::copy(left, right, sTemp.begin());
            vList.push_back(sTemp.c_str());
            iter = right;
        }
        return true;
    }
};

void runPointCloudCmd() {

    AcApDocument* pDoc = curDoc();
    if (!pDoc)
        return;
    AcDbDatabase* pDb = pDoc->database();
    if (!pDb)
        return;

    PromptKwd promptKwd(IDS_PROMPT_CMD, IDS_INP_KWD_CMD);
    if (!promptKwd.isValid())
        return;
    promptKwd.addDefOption(5);
    AcDbObjectIdArray objectIdArray;
    bool bDone      = false;
    bool bOpenCloud = false;
    AcString path;

    do {
        NCHAR sWord[20] = { _T("\0") };
        acedInitGet(RSG_NONULL, promptKwd.getKwd());
        int iInput = acedGetKword(promptKwd.getPrompt(), sWord);
        switch (iInput)
        {
        case RTCAN:
            return;
        case RTNORM:
        case RTKWORD:
        {
            iInput = promptKwd(sWord);
            if (iInput != INP_KEYWORD && (iInput != INP_KEYWORD + 4) && !bOpenCloud) {
                acutPrintf(promptKwd.getString(IDS_ERR_OPEN));
                break;
            }
            switch (iInput)
            {
            case INP_KEYWORD:
            {
                AcString sLoadFilter = promptKwd.getString(IDS_SUPPORT_FORMAT);
                AcString sPrompt = promptKwd.getString(IDS_PROMPT_LOAD);
                if (path.isEmpty())
                    path = promptKwd.getPathModule();
                CFileDialog dlgOpen(true, nullptr, nullptr, OFN_PATHMUSTEXIST |
                    OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ENABLESIZING, sLoadFilter);
                dlgOpen.GetOFN().lpstrInitialDir = path;
                dlgOpen.GetOFN().lpstrTitle = sPrompt;
                if (dlgOpen.DoModal() != IDOK)
                    break;

                AcString sFileName = dlgOpen.GetOFN().lpstrFile;
                path = sFileName;
                path = path.substr(path.findRev(_T("\\")));
                if (!PointCloudBridge::createPointCloudFromFile(pDoc, sFileName, objectIdArray, true))
                {
                    acutPrintf(promptKwd.getString(IDS_ERR_OPEN));
                }
                else
                    bOpenCloud = true;
                break;
            }
            case INP_KEYWORD + 1:
            {
                for (auto const& objectId : objectIdArray)
                {
                    PointCloudInsertion pointCloud      = PointCloudBridge::asPointCloudInsertion(objectId, NcDb::kForWrite);
                    VisualizationParams visualParams    = pointCloud.createVisualizationParamsSet();
                    ColoringByElevation coloringElev(pDoc);
                    visualParams.setColoringParams(coloringElev);
                }
                break;
            }
            case INP_KEYWORD + 2:
            {
                resbuf rb;
                if (acedGetVar(_T("CVPORT"), &rb) != RTNORM) {
                    acutPrintf(promptKwd.getString(IDS_ERR_CLIPPING));
                    break;
                }
                int iVport = rb.resval.rint;
                if (acedGetVar(_T("TILEMODE"), &rb) != RTNORM) {
                    acutPrintf(promptKwd.getString(IDS_ERR_CLIPPING));
                    break;
                }
                int iTile = rb.resval.rint;
                if (iTile == 0 && iVport == 1) {
                    acutPrintf(promptKwd.getString(IDS_ERR_PAPER));
                    break;
                }
                AcDbObjectId vpId = acedViewportIdFromNumber(iVport);
                assert(!vpId.isNull());
                AcDbObject* pVpObj = nullptr;
                if (acdbOpenObject(pVpObj, vpId, AcDb::kForRead) != Acad::eOk) {
                    acutPrintf(promptKwd.getString(IDS_ERR_CLIPPING));
                    break;
                }
                AcDbViewportTableRecord* pViewportTabRec = AcDbViewportTableRecord::cast(pVpObj);
                assert(pViewportTabRec != nullptr);
                AcGsView* pGsView = pViewportTabRec->gsView();
                assert(pGsView != nullptr);
                AcGeMatrix3d mtView = pGsView->viewingMatrix();

                AcGePoint3d pt1, pt2;
                acedInitGet(NULL, nullptr);
                iInput = acedGetPoint(nullptr, promptKwd.getString(IDS_INP_FIRST_POINT), (nds_real*)&pt1);
                if (iInput != RTNORM)
                    break;
                acedInitGet(NULL, nullptr);
                iInput = acedGetPoint(nullptr, promptKwd.getString(IDS_INP_OPPOSITE_CORNER), (nds_real*)&pt2);
                if (iInput != RTNORM)
                    break;
                pt1.transformBy(mtView);
                pt2.transformBy(mtView);
                AcGePoint2d pt2d_1(pt1.x, pt1.y);
                AcGePoint2d pt2d_2(pt2.x, pt2.y);

                _ViewportHandle vpHandle = vpId.handle();
                GeometryClippingElement geomClipping;
                geomClipping.setRectangle(pt2d_1, pt2d_2);
                geomClipping.setZMin(-FLT_MAX);
                geomClipping.setZMax(FLT_MAX);
                geomClipping.transformBy(mtView);
                geomClipping.setInverted(false);
                for (auto const& objectId : objectIdArray)
                {
                    PointCloudInsertion pointCloud  = PointCloudBridge::asPointCloudInsertion(objectId, NcDb::kForWrite);
                    VisualizationParams dstParams   = pointCloud.getVisualizationParamsSet(vpHandle);
                    VisualizationParams newParams   = pointCloud.createVisualizationParamsSet();
                    newParams.changeClipping(geomClipping);
                    newParams.setPointSize(dstParams.getPointSize());
                    pointCloud.setVisualizationParamsSetToViewport(newParams, vpHandle);
                }
                break;
            }
            case INP_KEYWORD + 3:
            {
                DWORD nTypeIndex = 0;
                AcString sExportFilter  = promptKwd.getString(IDS_EXPORT_FORMAT);
                AcString sPrompt        = promptKwd.getString(IDS_PROMPT_EXPORT);
                if (path.isEmpty())
                    path = promptKwd.getPathModule();
                CFileDialog dlgFile(false, nullptr, nullptr, OFN_HIDEREADONLY |
                    OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_EXPLORER, sExportFilter);
                dlgFile.GetOFN().lpstrTitle         = sPrompt;
                dlgFile.GetOFN().nFilterIndex       = nTypeIndex;
                dlgFile.GetOFN().lpstrInitialDir    = path;
                if (dlgFile.DoModal() != IDOK)
                    break;

                AcString sFilePath = dlgFile.GetPathName().GetBuffer();
                int endPath        = sFilePath.findRev(_T("\\"));
                path               = sFilePath.substr(endPath++);
                AcString sFileName = sFilePath.substr(endPath, sFilePath.length() - endPath);
                nTypeIndex         = dlgFile.GetOFN().nFilterIndex;
                fileType type = fileType(nTypeIndex);
                if (!PointCloudBridge::savePointCloudAsFile(objectIdArray,
                    type, sFileName, path, true, true))
                {
                    acutPrintf(promptKwd.getString(IDS_ERR_WRITING_FILE));
                }
                break;
            }
            case INP_KEYWORD + 4:
                bDone = true;
                break;
            }
            break;
        }
        default:
            bDone = true;
            break;
        }
    } while (!bDone);
}



