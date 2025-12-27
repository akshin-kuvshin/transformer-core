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

#ifndef __OPENDWGTHUNKHOSTTYPES_H__
#define __OPENDWGTHUNKHOSTTYPES_H__

#include "nrxdbgate/typesDb.h"
#include "nrxhostgate_impexp.h"

#define ncrxClassDictionary \
	GetClassDictionary()

#define ncrxServiceDictionary \
	GetServiceDictionary()

namespace NcCm
{
	enum DialogTabs
	{
		kACITab       = 1,
		kTrueColorTab = 2,
		kColorBookTab = 4,
	};

	enum NCIColors
	{
		kACIByBlock    = 0,
		kACIRed        = 1,
		kACIYellow     = 2,
		kACIGreen      = 3,
		kACICyan       = 4,
		kACIBlue       = 5,
		kACIMagenta    = 6,
		kACIForeground = 7,
		kACIByLayer    = 256,
	};
}

enum
{
	INP_NNULL   = RSG_NONULL,
	INP_NZERO   = RSG_NOZERO,
	INP_NNEG    = RSG_NONEG,
	INP_NLIM    = RSG_NOLIM,
	INP_DASH    = RSG_DASH,
	INP_NZCOORD = RSG_2D
};

__declspec(dllexport) typedef enum
{
	kNdUiNotify_Nothing,
	kNdUiNotify_Generic,
	kNdUiNotify_AppMainWindow,
	kNdUiNotify_AppResourceInstance,
	kNdUiNotify_AutoLoad,
	kNdUiNotify_Reload,
	kNdUiNotify_GetTipSupport,
	kNdUiNotify_GetTipText,
	kNdUiNotify_GetTipRect,
	kNdUiNotify_HitTipRect,
	kNdUiNotify_DrawTip,
	kNdUiNotify_DrawTipText,
	kNdUiNotify_UpdateTip,
	kNdUiNotify_HideWindow,
	kNdUiNotify_ShowWindow,
	kNdUiNotify_RestoreFocus,
	kNdUiNotify_Change,
	kNdUiNotify_NotValid,
	kNdUiNotify_Valid,
	kNdUiNotify_Validate,
	kNdUiNotify_CommandState,
} NDUI_NOTIFY;

__declspec(dllexport) typedef enum
{
	kNdUiReply_Nothing,
	kNdUiReply_Ok,
	kNdUiReply_NotValid,
	kNdUiReply_Valid,
	kNdUiReply_TextTip,
	kNdUiReply_ToolTip,
	kNdUiReply_DrawTip,

} NDUI_REPLY;

typedef enum
{
	kNdUiCommand_Cancelled = -1,
	kNdUiCommand_Completed,
	kNdUiCommand_Begun,

} NDUI_COMMAND_STATE;

enum NcEdDrawOrderCmdType
{
	kDrawOrderNone = 0,
	kDrawOrderBottom,
	kDrawOrderTop,
	kDrawOrderBelow,
	kDrawOrderAbove
};

enum NcadContextMenuMode
{
	kDefault = 0,
	kEdit,
	kCommand,
	kHotGrip,
	kOsnap,
};

enum xrefSubcommandActivities
{
	kStart            = 0,
	kStartItem        = 2,
	kEndItem          = 3,
	kEnd              = 4,
	kWillAbort        = 5,
	kAborted          = 6,
	kStartXBindBlock  = 7,
	kStartXBindSymbol = 8
};

enum undoSubcommandActivities
{
	kNone = 0,
	kOne  = 1,
	kAll  = 2
};


#define ODRX_DEFINE_DOCUMENT_REACTOR(_UserReactorClass) \
	static _UserReactorClass g_pDocumentReactor = 0;


#define NCRX_CLASS_DICTIONARY         NCRX_T("ClassDictionary")
#define NCRX_DYNAMIC_LINKER           NCRX_T("DynamicLinker")
#define NCRX_SERVICE_DICTIONARY       NCRX_T("ServiceDictionary")
#define NCRX_KERNEL_SERVICES          NCRX_T("KernelServices")
#define NCRX_PROTOCOL_REACTOR_MANAGER NCRX_T("ProtocolReactorManager")


#endif // __OPENDWGTHUNKHOSTTYPES_H__
