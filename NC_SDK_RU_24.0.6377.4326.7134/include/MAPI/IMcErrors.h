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

#pragma once

#ifdef _VERBOSEHEADERS_
#pragma message("Use " __FILE__)
#endif

//===========================================================================
// MechaniCS HRESULT codes

// AGL comment: 
// error codes (low 16 bits) must be greater than 0x200,
// let's use values greater than 0xBA00

enum mcsErrs
{
	MCS_S_COMMAND         = MAKE_HRESULT(0, FACILITY_ITF, 0xBA00 + 1),     // 0x0004BA01
	MCS_S_GOANOTHERWAY,                                                    // 0x0004BA02
	MCS_S_DRAW_BODY,                                                       // 0x0004BA03
	MCS_S_GOBACK,                                                          // 0x0004BA04
	MCS_S_NO_TRANSFORM,                                                    // 0x0004BA05
	MCS_S_EXPLODE_AGAIN,                                                   // 0x0004BA06
//	MCS_S_INDEX_PROPERTY, упразднено                                                 // 0x0004BA07 getProperty() возвращает для свойств типа MCS_COMBOBOX_STRING_INDEX
	MCS_S_DISABLE_EDIT,                                                    // 0x0004BA08 getProperty(MCS_PROPERTY_INFO,...) возвращает в случае, если надо запретить редактирование через всплывающую подсказку
	MCS_S_DIMVALUE_SET,                                                    // 0x0004BA09 IEntityMonitor::GetEntity возвращает в случае успешного срабатывания SetDimValues при работе с динамическими размерами
	MCS_S_CHILD_UPDATED,                                                   // 0x0004BA0A
	MCS_S_NEED_UPDATE_PARENT,                                              // 0x0004BA0B IMcEntity::onUpdate can query parent update via this retcode
	MCS_S_REQUERY_LIST,                                                    // 0x0004BA0C setProperty возвращает в случае необходимости обновить список свойств после изменения данного свойства
	MCS_S_REUSE_EXISTING_SUBDOC,                                           // 0x0004BA0D возвращает IMcDocument::repairSubDocumentName в режиме kMcFixSubDocNameMode_AskForReuseExisting, когда фиксация имени дала имя существующего поддокумента и пользователь подтвердил его использование

	MCS_E_DUP_ID_FOUND    = MAKE_HRESULT(0, FACILITY_ITF, 0xBA00 + 0x100), // 0x0004BB00 -- error: id duplication

	// errors
	MCS_E_NO_CONNECTION   = MAKE_HRESULT(1, FACILITY_ITF, 0xBA00 + 3),     // 0x8004BA03
	MCS_E_NULL_BUFFER,                                                     // 0x8004BA04
	MCS_E_AMBIGUOUS,                                                       // 0x8004BA05
	MCS_E_STREAM_NEWER_VER,                                                // 0x8004BA06
	MCS_E_STREAM_UNSUPPORTED_TYPE,                                         // 0x8004BA07
	MCS_E_STREAM_INTENRNAL_ERROR,                                          // 0x8004BA08
	MCS_E_STREAM_INVALID_TAG,                                              // 0x8004BA09
	MCS_E_STREAM_INVALID_DATA,                                             // 0x8004BA0A
	MCS_E_STREAM_INVALID_POSITION,                                         // 0x8004BA0B
	MCS_E_NOT_IN_DATABASE,                                                 // 0x8004BA0C
	MCS_E_OBJECT_NOTFOUND,                                                 // 0x8004BA0D
	MCS_E_CANT_REINIT_OBJECT,                                              // 0x8004BA0E
	MCS_E_OBJECT_IS_INVALIDATED,                                           // 0x8004BA0F
	MCS_E_MAKE_ME_PROXY,                                                   // 0x8004BA10
	MCS_E_PARAMS_LOADED,                                                   // 0x8004BA11
	MCS_E_BUFFER_TOO_SMALL,                                                // 0x8004BA12
	MCS_E_BL_TOOLONG,                                                      // 0x8004BA13
	MCS_E_BL_INVALIDSEG,                                                   // 0x8004BA14
	MCS_E_BL_CANNOTDEL,                                                    // 0x8004BA15
	MCS_E_BL_COMMONSURF,                                                   // 0x8004BA16
	MCS_E_PROPERTY_NOT_FOUND,                                              // 0x8004BA17
	MCS_E_GEARS_CANNOTFINDANGLE,                                           // 0x8004BA18
	MCS_E_GEARS_FAILED_ZSUM,                                               // 0x8004BA19
	MCS_E_GEARS_FAILED_Z,                                                  // 0x8004BA1A
	MCS_E_GEARS_FAILED_X,                                                  // 0x8004BA1B
	MCS_E_UNSUPP_VERSION,                                                  // 0x8004BA1C
	MCS_E_STREAM_COMPRESSION_ERROR,                                        // 0x8004BA1D
	MCS_E_OBJECT_READ_ONLY,                                                // 0x8004BA1E
	MCS_E_MULTIPLE_OBJECTS,                                                // 0x8004BA1F
	MCS_E_FINISH_ME,                                                       // 0x8004BA20
	MCS_E_OBJECT_ERASED,                                                   // 0x8004BA21
	MCS_E_GEARS_A_TW,                                                      // 0x8004BA22
	MCS_E_LAYER_LOCKED,                                                    // 0x8004BA23
	MCS_E_NO_TEMLATE,                                                      // 0x8004BA24
	MCS_E_STREAM_CRC_ERROR,                                                // 0x8004BA25

	MCS_E_CTR3D_CANNOT_SOLVE,                                              // 0x8004BA26
	MCS_E_CTR3D_OVERCONSTRAINED,                                           // 0x8004BA27
	MCS_E_CTR3D_CYCLIC_DEPENDENCE,                                         // 0x8004BA28
	MCS_E_CTR3D_DUPLICATED,                                                // 0x8004BA29
	MCS_E_CTR3D_NOT_SATISFIED,                                             // 0x8004BA2A
	MCS_E_CTR3D_UNSOLVABLE,                                                // 0x8004BA2B
	MCS_E_CTR3D_MATED_FIXATION,                                            // 0x8004BA2C
	MCS_E_CTR3D_DRAGGING_FAILED,                                           // 0x8004BA2D
	MCS_E_CTR3D_NEED_TO_BE_EVALUATED,                                      // 0x8004BA2E
	MCS_E_CTR3D_LOST_GEOMETRY                                              // 0x8004BA2F  Случай, когда методы типа Mc3dConstraintInfo::getGeometry1() возращают ошибку.
};
//===========================================================================

