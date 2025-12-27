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

// AGL: DO NOT PUT HERE ANY OTHER HEADERS, 
// do it below macro MECHCTL_NO_FMC definition
#include <commctrl.h>

#include "IMcObjectsNumerator.h"
#include "IMcMeasure.h"
#include "IMcStyles.h"
#include "mcstempl.h"
#include "McAPIs.h"
#include "DynLoadMacro.h"
#include "MCSConsts.h"

enum McImagesEnum {
//-------------------------------------
//Первая порция иконок
//-------------------------------------
	ID_IMG_HELP = 0,                //Help
	ID_IMG_REFRESH,                 //Refrsh
	ID_IMG_CREATE,                  //Create
	ID_IMG_DELETE,                  //Delete (крестик)
	ID_IMG_CONSTRAINT_MATE,         //Зависимость Mate
	ID_IMG_CONSTRAINT_INSERT,       //Зависимость Insert
	ID_IMG_CONSTRAINT_ANGLE,        //Зависимость Angle
	ID_IMG_CONSTRAINT_PARAMETERS,   //Зависимость Parameters
	ID_IMG_CONSTRAINT_AXIS,         //Зависимость Axis
	ID_IMG_CONSTRAINT_RELATION,     //Зависимость Relation
	ID_IMG_CONSTRAINT_DIRECTION,		//Зависимость Direction
	ID_IMG_CONSTRAINT_RESERVED,
	ID_IMG_CONSTRAINT_SINGLEDIRECT, //Однонаправленная зависимость
	ID_IMG_CONSTRAINT_BIDIRECT,     //Двунаправленная зависимость
	ID_IMG_CONSTRAINT_CONTRDIRECT,  //Противонаправлено
	ID_IMG_CONSTRAINT_CODIRECT,     //Сонаправлено
	ID_IMG_EDIT,                    //Edit 
	ID_IMG_LOCKED,                  //Locked
	ID_IMG_UNLOCKED,                //UnLocked
	ID_IMG_LAMP_GREEN,              //Зеленая лампочка
	ID_IMG_LAMP_RED,                //Красная лампочка
	ID_IMG_HIDEN_OBJECT,            //Серенький объект
	ID_IMG_NEW_FOLDER,              //Новая папка
	ID_IMG_INSERTOBJECT,            //Вставить объект из броузера в доркумент
	ID_IMG_PREVIEW,                 //Превиев
	ID_IMG_OBJECT,									//Стандартный объект
	ID_IMG_DOCUMENT,								//Документ содержащий объекты
	ID_IMG_ROOT,                    //ROOT
	ID_IMG_NOTE_ADD,                //Выноски: добавить строку
	ID_IMG_NOTE_REMOVE,             //Выноски: удалить строку
	ID_IMG_NOTE_SIMPLE,             //Выноски: простая выноска
	ID_IMG_NOTE_CORNER,             //Выноски: многострочная выноска
	ID_IMG_ARR_NONE,                //Стрелка: Без стрелки
	ID_IMG_ARR_ARROW,               //Стрелка: Стрелка
	ID_IMG_ARR_POINT,               //Стрелка: Точка
	ID_IMG_ARR_OPEN,                //Стрелка: Открытая стрелка
	ID_IMG_ARR_HALF,                //Стрелка: Полустрелка
	ID_IMG_ALIGN_LEFT,              //Выравнивание по левому краю
	ID_IMG_ALIGN_CENTER,            //Выравнивание по центру
	ID_IMG_ALIGN_RIGHT,             //Выравнивание по правому краю
	ID_IMG_SPECSYMB,                //Спецсимволы
	ID_IMG_ADDLEADER,               //Добавить линию-выноску
	ID_IMG_MATCHPROP,               //Копирование свойств
	ID_IMG_NOTE_SURFACE,            //Выноски: поверхность
	ID_IMG_NOTE_DIM,                //Выноски: размер
	ID_IMG_NOTE_OTHER,              //Выноски: другое
	ID_IMG_SYM_DIAMETER,            //Спецсимвол: диаметр
	ID_IMG_SYM_GRADUS,              //Спецсимвол: градус
	ID_IMG_SYM_PLUSMINUS,           //Спецсимвол: плюс-минус
	ID_IMG_SYM_PARAGRAPH,           //Спецсимвол: параграф
	ID_IMG_SYM_SNAKE,               //Спецсимвол: змейка
	ID_IMG_SYM_QUOTE,               //Спецсимвол: открывающая кавычка
	ID_IMG_SYM_UNQUOTE,             //Спецсимвол: закрывающая кавычка
	ID_IMG_SYM_NUMBER,              //Спецсимвол: номер
	ID_IMG_SYM_LGRADIENT,           //Спецсимвол: уклон влево
	ID_IMG_SYM_RGRADIENT,           //Спецсимвол: уклон вправо
	ID_IMG_SYM_LCONICITY,           //Спецсимвол: конусность влево
	ID_IMG_SYM_RCONICITY,           //Спецсимвол: конусность вправо
	ID_IMG_SYM_DOG,                 //Спецсимвол: собака
	ID_IMG_SYM_PI,                  //Спецсимвол: Пи
	ID_IMG_SYM_RTCORNER,            //Спецсимвол: уголок
	ID_IMG_SYM_CANCEL,              //Спецсимволы - отмена
	ID_IMG_EMPTY,                   //Пустой квадрат
	ID_IMG_SURF_DIR1,               //Шероховатость: направление неровностей
	ID_IMG_SURF_DIR2,               //Шероховатость: направление неровностей
	ID_IMG_SURF_DIR3,               //Шероховатость: направление неровностей
	ID_IMG_SURF_DIR6,               //Шероховатость: направление неровностей
	ID_IMG_SURF_DIR5,               //Шероховатость: направление неровностей
	ID_IMG_SURF_DIR4,               //Шероховатость: направление неровностей
	ID_IMG_MARK_MARK,               //Маркировка - маркировка
	ID_IMG_MARK_STAMP,              //Маркировка - клеймение
	ID_IMG_SELECT_LINE,             //Выбрать линию
	ID_IMG_OPTIONS,                 //Параметры
	ID_IMG_GOST,                    //Гост
	ID_IMG_SURF_DIM,                //Шероховатость - связь с размером
	ID_IMG_ARR_OBLIQUE,             //Стрелка: Засечка
	ID_IMG_MULTIPLE_INSERT,         //"Вставить несколько"
	ID_IMG_AUTO_REPEAT,             //Автоповтор
	ID_IMG_METAL1,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL2,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL3,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL4,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL5,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL6,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL7,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL8,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL9,                  //Спецсимволы: металлопрокат
	ID_IMG_METAL10,                 //Спецсимволы: металлопрокат
	ID_IMG_METAL11,                 //Спецсимволы: металлопрокат
	ID_IMG_METAL12,                 //Спецсимволы: металлопрокат
	ID_IMG_METAL13,                 //Спецсимволы: металлопрокат
	ID_IMG_METAL14,                 //Спецсимволы: металлопрокат
	ID_IMG_METAL15,                 //Спецсимволы: металлопрокат
	ID_IMG_METAL16,                 //Спецсимволы: металлопрокат
	ID_IMG_POW2,                    //Спецсимволы: степень 2
	ID_IMG_POW3,                    //Спецсимволы: степень 3
	ID_IMG_DELTA,                   //Спецсимволы: малая дельта
	ID_IMG_SINGLE_STROKE,           //Выноски: один штрих
	ID_IMG_DOUBLE_STROKE,           //Выноски: два штриха
	ID_IMG_RULER,                   //Линейка
	ID_IMG_MATERIALS,               //значек базы Материалы
	ID_IMG_EDITTEXT,                //редактировать текст
	ID_IMG_FORMAT,									//иконка форматов
	ID_IMG_OPEN_OPTIONS,						//открыть опции
	ID_IMG_SAVE_OPTIONS,						//сохранить опции
	ID_IMG_SURF,										//Шерховатость
	ID_IMG_CORNER_STAMP,							//Угловой штамп
	ID_IMG_CHANGE_ARBOR_SEGMENT,			//Сменить тип сегмента вала
	ID_IMG_VS_TURNED,	    		      //Виды - повернуто
	ID_IMG_VS_UNFOLDED,			        //Виды - развернуто
	ID_IMG_DOWN,										//Стрелка вниз (как в ComboBox)
	ID_IMG_DIALOG,									//Многоточие (для кнопки вызова диалога)
	ID_IMG_ASSOCIATION,							//Зависимость
	// Стрелки
	ID_IMG_ARROW_NONE,
	ID_IMG_ARROW_ARROW,
	ID_IMG_ARROW_DOT,
	ID_IMG_ARROW_OBLIQUE,
	ID_IMG_ARROW_BASE,
	ID_IMG_ARROW_OPEN,
//-------------------------------------
//Далее идет вторая порция иконок
//-------------------------------------
	ID_IMG_ARROW_HALF,
	ID_IMG_ARROW_LEG,
	ID_IMG_ARROW_OPEN90,
	ID_IMG_ARROW_UNKNOWN,
	ID_IMG_FIX_SYMBOL1,
	ID_IMG_FIX_SYMBOL2,
	ID_IMG_FIX_SYMBOL3,
	ID_IMG_FIX_SYMBOL4,
	ID_IMG_FIX_SYMBOL5,
	ID_IMG_FIX_SYMBOL6,
	ID_IMG_FIX_SYMBOL7,
	ID_IMG_FIX_OK,
	ID_IMG_FIX_CANCEL,
	ID_IMG_FIX_SYMBOL8,
	ID_IMG_FIX_SYMBOL9,
	ID_IMG_FIX_BOUNDARY,
	ID_IMG_FIX_WELDPOINT,
	ID_IMG_FIX_SUMMARY,

	ID_IMG_TOL_M,                   // Зависимый допуск
	ID_IMG_TOL_P,                   // Выступающее поле допуска
	ID_IMG_TOL_ADDLEADERBASE,       // Добавить линию-выноску
	ID_IMG_TOL_SELBASE,             // Выбрать обозначение базы
	ID_IMG_TOL_ADDBASE,             // Создать обозначение базы
	ID_IMG_TOL_DIV,                 // Вставить разделитель
	ID_IMG_HATCH_SIDE,                 
	ID_IMG_FILL_SELECT,             // Выбрать отверстия/окружности
	ID_IMG_FILL_SET,                // Отрисовать отверстие
	ID_IMG_SYM_SQUARE,              // Обозначение квадрата
	ID_IMG_FITS,                    // Таблица допусков и посадок

	ID_IMG_VIEW_DIM,                // Редактирование viewport`а
	ID_IMG_VIEW_ACTIVATE,           // Редактирование viewport`а
	ID_IMG_VIEW_LOCK,               // Редактирование viewport`а
	ID_IMG_VIEW_UNLOCK,             // Редактирование viewport`а
	ID_IMG_VIEW_ZOOMALL,            // Редактирование viewport`а
	ID_IMG_VIEW_CUT,                // Редактирование viewport`а
	ID_IMG_ANKER,                   // Якорь

	ID_IMG_SURF_DIR7,               //Шероховатость: направление неровностей

	ID_IMG_SETOBJ_SCALE,            // Диалог масштаба
	ID_IMG_GETOBJ_SCALE,            // Диалог масштаба 
	ID_IMG_MARKER_WITH_LINE,        // Маркер с линией
	ID_IMG_MARKER_WITHOUT_LINE,     // Маркер без линии 
	ID_IMG_PLOTED,									// Печатный
	ID_IMG_UNPLOTED,								// Непечатный
	ID_IMG_DRAWING,                 // Чертеж
	ID_IMG_SELECT_ENTS,             // Селектировать ентити рамкой		
	ID_IMG_MARKER_ALIGN,            // поворачивать относительно линии		
	ID_IMG_SAVE,										// Сохранить		
	ID_IMG_UNIQUE_INC,							// Тип поля - автоинкремент		
	ID_IMG_SELECTION_TYPE_ADD,			// Добавить в селекцию		
	ID_IMG_SELECTION_TYPE_NEW,			// Новая селекция		
	ID_IMG_SELECTION_TYPE_SUB,			// Вычесть из селекции		
	ID_IMG_EMPTY_IMG,								// Пустой (дисейбленный) rect; для списка.
	ID_IMG_EMPTY_TREE_PLUS,					// Плюс в дереве				
	ID_IMG_EMPTY_TREE_MINUS,				// Минус в дереве

	// Иконки объектов
	ID_IMG_ENT_NOTEP,	        			// Позиционная выноска
	ID_IMG_ENT_NOTEC,       				// Гребенчатая выноска
	ID_IMG_ENT_NOTEH,	    					// Цепная выноска
	ID_IMG_ENT_NOTEK,			  		  	// Узловая выноска
	ID_IMG_ENT_NOTES,				    		// Узловая секущая выноска
	ID_IMG_ENT_NOTEM,					    	// Выноска для многослойных конструкций
	ID_IMG_ENT_LINM,				        // Маркировка линейных объектов
	ID_IMG_ENT_PL,				          // Дополнительная линия-выноска
	ID_IMG_ENT_VIEW,				        // Вид
	ID_IMG_ENT_SECT,				        // Разрез, сечение
	ID_IMG_ENT_VSDESC,				      // Обозначение вида, разреза...
	ID_IMG_ENT_EVIEW,				        // Выносной вид
	ID_IMG_ENT_HOLEFILL,				    // Заливка отверстий
	ID_IMG_ENT_MARK,				        // Маркирование и клеймение
	ID_IMG_ENT_SURF,				        // Шероховатость поверхности
	ID_IMG_ENT_TOL,				          // Допуск формы и расположения

	ID_IMG_NOTEBOOK,                // Записная книжка
	ID_IMG_DIM_LINEAR,              // Иконки размеров в дереве объектов
	ID_IMG_DIM_RADIAL,
	ID_IMG_DIM_DIAMETER,
	ID_IMG_DIM_ANGULAR,
	ID_IMG_DIM_ARC,
	ID_IMG_DIM_HUGE,
	ID_IMG_DIM_ORDINATE,
	ID_IMG_OVERLAY1,								//Оверлый для индикации скрытых объектов
	ID_IMG_UNI_MARKER,							//Иконка уневерсального маркера
	ID_IMG_GROUP_MARKER,						//Иконка маркера группы
	ID_IMG_OVERLAY2,								//Оверлый для индикации рутов
	ID_IMG_DIRECTION_LEFT,					//Направление налево
	ID_IMG_DIRECTION_RIGHT,					//Направление напараво

	// Для записной книжки
	ID_IMG_OPENBOOK_ADD,		// Добавить раздел
	ID_IMG_PAGE_ADD,			// Добавить страницу
	ID_IMG_PAGE_REMOVE,			// Удалить страницу
	ID_IMG_PAGE_EDIT,			// Редактировать страницу
	ID_IMG_OPEN,				// Открыть
	ID_IMG_SAVE_YELLOW,			// Сохранить
	ID_IMG_BOOK_ADD,			// Добавить раздел
	ID_IMG_BOOK_REMOVE,			// Удалить раздел
	// Тех требования
	ID_IMG_CLEAR_ALL,			// Очистить все
	ID_IMG_INSERT_ITEM,			// Добавить пункт ТТ
	ID_IMG_REMOVE_ITEM,			// Удалить пункт ТТ
	ID_IMG_MOVE_DOWN,			// Переместить вниз
	ID_IMG_MOVE_UP,				// Переместить вверх
	ID_IMG_SUPER_SCRIPT,		// Верхний индeкс
	ID_IMG_SUB_SCRIPT,			// Нижний индeкс
	ID_IMG_FRAC,				// Вставить дробь
	ID_IMG_TOLERANCE,			// Вставить допуск
	ID_IMG_MATERIAL,			// Вставить материал
	ID_IMG_INSERT_POSITION,		// Вставить позицию в текст
	ID_IMG_INSERT_VIEW,			// Вставить вид/разрез в текст
	ID_IMG_BOOK,				// Книга
	ID_IMG_OPENBOOK,			// Открытая книга
	ID_IMG_PAGE,				// Страница
	ID_IMG_PAGE_TABLE,			// Страница с таблицей
	ID_IMG_NOTEBOOK_OPEN,		// Открыть записную книжку
	// Спецификация
	ID_IMG_LINK_POSITION,		// Связать позицию с файлом
	ID_IMG_UNLINK_POSITION,		// Разорвать связь
	ID_IMG_CUT,					// Вырезать
	ID_IMG_COPY,				// Копировать
	ID_IMG_PASTE,				// Вставить
	ID_IMG_SPECIFICATION,		// Спецификация
	ID_IMG_PROPERTIES,			// Свойства
	ID_IMG_REFRESH_SPC,			// Обновить спецификацию на чертеже

//-------------------------------------
//Далее идет третья порция иконок
//-------------------------------------
	ID_IMG_AUTO_NUMBER_SPC,		// Пронумеровать позиции
	ID_IMG_EXPORT_TO_DRAWING,	// Экспортировать на чертеж
	ID_IMG_EXPORT_TO_EXCEL,		// Экспортировать в Excel
	ID_IMG_EXPORT_TO_TCS,		// Экспортировать в TCS
	ID_IMG_SET_LEADER,			// Задать выноску для записи позиции
	ID_IMG_ADD_TO_LEADER,		// Добавить позицию в существующую выноску
	ID_IMG_FIND,				// Найти
	ID_IMG_TABLE_ADD,			// Добавить таблицу
	ID_IMG_GRID_INSERT_ROW,		// Вставить столбец в таблицу
	ID_IMG_GRID_DELETE_ROW,		// Удалить столбец из таблицы
	ID_IMG_GRID_INSERT_COLUMN,	// Вставить колонку в таблицу
	ID_IMG_GRID_DELETE_COLUMN,	// Удалить колонку из таблицы
	ID_IMG_GRID_RENAME_COLUMN,	// Переименовать столбец
	ID_IMG_SELECT_JOINT_PLACMENT_DYN,				//Селекция местоположения и расположения отверстий для сборки с чертежа
	ID_IMG_SELECT_JOINT_PLACMENT_MANUAL,		//Селекция местоположения и расположения отверстий из диалога
	ID_IMG_BREAK_LINEAR,		//обрывы/разрывы
	ID_IMG_BREAK_TWOLINEAR,
	ID_IMG_BREAK_CURVED,
	ID_IMG_BREAK_TWOCURVED,
	ID_IMG_BREAK_TUBULAR,
	ID_IMG_CALC_ARROW_LEFT,								//Стрелки для калькулятора
	ID_IMG_CALC_ARROW_RIGHT,
	ID_IMG_CALC_ARROW_UP,
	ID_IMG_CALC_ARROW_DOWN,
	ID_IMG_DIGICALC,											//Калькулятор
	ID_IMG_SQRT,
	ID_IMG_OPEN_FORLDER,									//Папка со стрелочкой
	ID_IMG_TEXT_ALIGNMENT,			// Точка выравнивания
	ID_IMG_SELECT_DYNAMICALY,			// Кнопка разрешения динамического выбора
	// Для измерителя
	ID_IMG_MEASURE_TEXT,          // Схема измерения: взять с текста
	ID_IMG_MEASURE_PERIMETER,     // Схема измерения: измерить периметр или длину траектории
	ID_IMG_MEASURE_AREA,          // Схема измерения: измерить площадь
	ID_IMG_MEASURE_DISTANCE,      // Схема измерения: измерить расстояние
	ID_IMG_MEASURE_ANGLE,         // Схема измерения: измерить угол
	// Символы для размеров (продолжение)
	ID_IMG_SYM_SR,                  // SR
	ID_IMG_SYM_SDIAM,               // S + обозначение диаметра

	ID_IMG_ARR_CLOSEDBLANK,
	ID_IMG_ARR_OPEN90,
	ID_IMG_ARROW_INVERSE_HALF,
	ID_IMG_ARROW_CLOSED_BLANK,
	ID_IMG_ARROW_BASE_BLANK,
	ID_IMG_ARROW_DOT_BLANK,

	// Иконки для дерева. Смотрятся только на светлом фоне
	ID_IMG_TREE_ROOT,
	ID_IMG_TREE_ERROR,
	ID_IMG_TREE_FOLDER,
	ID_IMG_TREE_STANDARD,
	ID_IMG_TREE_DETAIL,
	ID_IMG_TREE_DRAWING_OPEN,
	ID_IMG_TREE_DRAWING,

	ID_IMG_OVERLAY3,         // Оверлей для индикации ссылок
	ID_IMG_BLOCK_REF,				//Иконка блока
	ID_IMG_DATUMTARGET,
	ID_IMG_FILTER,					//Вызов быстрой селекции
	// TABLE
	ID_IMG_TABLE,
	// GRID
	ID_IMG_GRID,
	// SQUARE
	ID_IMG_SQUARE,
	// AXIS
	ID_IMG_AXIS,
	// AXIS ORIENT
	ID_IMG_AXISORIENT,
	ID_IMG_CLIP_OFF,         //	Канцелярская кнопка (не фиксировать диалог)
	ID_IMG_CLIP_ON,          //	Канцелярская кнопка (фиксировать диалог)
	ID_IMG_SPRING,           // Пружина
	ID_IMG_CORR_MARKER,      // Маркер изменений СПДС
	ID_IMG_FRAGMENT,         // Обозначение фрагмента СПДС
	ID_IMG_LEVEL_MARKER,     // Отметка уровня СПДС
	ID_IMG_PLANE_LEVEL_MARKER,  // Отметка уровня на плане СПДС
	ID_IMG_NODE_MARKER,      // Обозначение узла СПДС
	ID_IMG_POLYMORPH_MARKER, // Универсальный маркер СПДС
	ID_IMG_SURFACE_MARKER,   // Обозначение обрабатываемой поверхности (выполняемого размера)
	ID_IMG_GRADIENT_MARKER,  // Обозначение уклона
	ID_IMG_GREEKCAP,
	ID_IMG_GREEK,
	ID_IMG_ENT_FIX,
	ID_IMG_ENT_BOUNDFORM,
	ID_IMG_ENT_WELD,
	ID_IMG_ENT_ANCHOR,
	ID_IMG_ENT_RANGE,
	ID_IMG_VS_ROTATED,				//Виды - повернуто
	ID_IMG_PLANE,							//Плоскости
	ID_IMG_PARAMETER_DIM,			//Размерный параметр
	ID_IMG_PARAMETER_DIM_READONLY,			//Размерный параметр только для чтения
	ID_IMG_PARAMETERS_ROOT,		//Кореневой элемент параметров
	ID_IMG_NORMACS,           // Вызов NormaCS. Иконка особо рекомендована Москвой
	ID_IMG_FD_GROUPBOX,       // Form deisgner
	ID_IMG_FD_PUSHBUTTON,
	ID_IMG_FD_LISTBOX,
	ID_IMG_FD_CHECKBOX,
	ID_IMG_FD_EDIT,
	ID_IMG_FEATURE_IDENTIFIER, // Иконка обозначения поверхности
	ID_IMG_IDF, // Микросхема
	ID_IMG_CALC, //Калькулятор прямоугольный китайский
	ID_IMG_FOREIGN, 
	ID_IMG_DB_ROOT_NORMAL,	// Root browser
	ID_IMG_DB_ROOT_OPEN,		// Root browser opened
	ID_IMG_DB_FOLDER,				// папка browserа
	ID_IMG_DB_FOLDER_OPEN,	// папка browserа opened
	ID_IMG_DB_DETAIL,				// деталь
	ID_IMG_DB_BINARY,				// файл
	ID_IMG_DB_DETAIL_DISABLED,				// деталь
	ID_IMG_DB_BINARY_DISABLED,				// файл
	ID_IMG_OCSEMPTY,
	ID_IMG_OCSFREE,
	ID_IMG_OCSOWN,
	ID_IMG_OCSFOREIGN,
	ID_IMG_DB_DETAIL_PARTIAL_ENABLED,				// деталь
	ID_IMG_DB_BINARY_PARTIAL_ENABLED,				// файл
	ID_IMG_DB_DETAIL_ENABLED,				// деталь
	ID_IMG_DB_BINARY_ENABLED,				// файл
	ID_IMG_PROPERTIES_RO,			// Свойства read only
	ID_IMG_FORM_EDITOR,				// Вызов редактора форм
	ID_IMG_SHOW_TREEE,			// Кнопка показывать дерево или нет
	ID_IMG_FD_COMBOBOX,                // Контрол: выпадающий список
	ID_IMG_FD_STATIC,                  // Контрол: текстовая метка
	ID_IMG_FD_RADIOBUTTON,             // Контрол: переключатель
	ID_IMG_FD_PANEL,                   // Контрол: выравнивающая панель
	ID_IMG_FD_IMAGE,                   // Контрол: картинка
	ID_IMG_NOTE_DULING,
	ID_IMG_KEYBOARD,
	ID_IMG_UNDO,
	ID_IMG_REDO,
	ID_IMG_NOTEM_LINE,
	ID_IMG_TAB_ORDER,
	ID_IMG_COPY_PROPS_TO,
	ID_IMG_NO_CTRL,
	ID_IMG_CONSTRAINT_SINGLE_DISABLED,	//Однонаправленная зависимость, gray
	ID_IMG_CONSTRAINT_BLOCKED,					//Заблокировання зависимость
	ID_IMG_ALIGN_TOP,
	ID_IMG_ALIGN_MIDDLE,
	ID_IMG_ALIGN_BOTTOM,

//-------------------------------------
//Далее идет четвертая порция иконок
//-------------------------------------

	// PlanTracer
	ID_IMG_BIG_PLUS,
	ID_IMG_BIG_MINUS,
	ID_IMG_ROOM,
	ID_IMG_FLAT,
	ID_IMG_FLOOR,
	ID_IMG_TABS_CTRL,
	ID_IMG_CALC_BEAM,                   // расчет балки
	ID_IMG_OVERLAY4,										//Мальенький замочек - толко для чтения
	ID_IMG_FAVORITES,										//Звезда Favorites
	ID_IMG_SEARCH_PANEL,
	ID_IMG_DOT,                         // Маркер группы в списках FormDesigner
	ID_IMG_CHECK_ACTIVE,
	ID_IMG_CHECK_GRAY,
	ID_IMG_VIEW_FRONT,									//Икона фронтального вида
	ID_IMG_VIEW_TOP,										//Икона вида сверху
	ID_IMG_VIEW_BOTTOM,									//Икона вида снизу
	ID_IMG_VIEW_LEFT,										//Икона вида слева
	ID_IMG_VIEW_RIGHT,									//Икона вида справа
	ID_IMG_VIEW_BACK,										//Икона вида ссзади
	ID_IMG_FILTRED_TABLE_CTRL,					//Иконка контрола таблица с фиьтрацией из форм
	ID_IMG_IMPL_VIEW_CTRL,							//Иконка контрола Упарвления видами и исполнениями
	ID_IMG_PREVIEW_CTRL,								//Иконка контрола Preview
	ID_IMG_MAGNET,
	ID_IMG_SYM_ENGNUMBER,
	// ISO WELD for MechaniCS
	ID_IMG_ENT_ISOWELD,
	ID_IMG_CLOSE_BUTTON,					//Кнопка закрыть XP стиль, как в загловках окон

	ID_IMG_NONE_ACAD_LAYER,

	ID_IMG_MEASURE_AREA_CPX,

	ID_IMG_PT_LAND,											// PT: земельный участок
	ID_IMG_PT_LAND_PART,								// PT: часть земельньнеого участка
	ID_IMG_PT_BUILDING,									// PT: строение
	ID_IMG_PT_BORDER,										// PT: ограда
	ID_IMG_PT_FLOOR,										// PT: этаж
	ID_IMG_SYM_POS,                     // Символ обозначения позиции СПДС

	ID_IMG_XREF_OVERLAY,								//Иконка xRef Overlay
	ID_IMG_XREF_ATTACH,								//Иконка xRef Attach
	ID_IMG_FD_DBLIST,                   // Контрол: список с заполнением из базы
	ID_IMG_FD_DBCOMBO,                  // Контрол: выпадающий список с заполнением из базы

	ID_IMG_ARROW_THICK_LINE,            // Стрелка "Толстая линия" (китайская база)
	ID_IMG_DATUM_IDENTIFIER,            // Иконка обозначения базы
	ID_IMG_ATTACH,                      // Присоеденить
	ID_IMG_OVERLAY5,										// это оверлэй ссылки с зеленым арзрешающим кружочком
	ID_IMG_OVERLAY6,										// Зеленый разрешающий кружочек в углу. используется для оверлэя в базах
	ID_IMG_MATH,

	//ППР
	ID_IMG_PPR_DUMPTRUCK,								//ППР: самосвал
	ID_IMG_PPR_BORING,									//ППР: сверло
	ID_IMG_PPR_HUMMER,									//ППР: молот
	ID_IMG_PPR_LIFTING,									//ППР: стрела крана

	// Границы ячеек в таблицах
	ID_IMG_BORDER_INNER,
	ID_IMG_BORDER_NONE,
	ID_IMG_BORDER_OUTER,
	ID_IMG_BORDER_ALL,
	ID_IMG_BORDER_LEFT,
	ID_IMG_BORDER_RIGHT,
	ID_IMG_BORDER_VERT,
	ID_IMG_BORDER_TOP,
	ID_IMG_BORDER_BOTTOM,
	ID_IMG_BORDER_HORZ,
	// Выравнивание текста
	ID_IMG_ALIGN_TOPLEFT,
	ID_IMG_ALIGN_TOPRIGHT,
	ID_IMG_ALIGN_BOTTOMLEFT,
	ID_IMG_ALIGN_BOTTOMRIGHT,
	
	ID_IMG_IMPORT_FROM_EXCEL,
	ID_IMG_TABLE_RANGE_MERGE,                         // группировать ячейки
	ID_IMG_TABLE_RANGE_UNMERGE,                       // разгруппировать ячейки
	ID_IMG_TABLE_RANGE_SPLIT,                         // переразбить ячейки (с изменением к-ва строк/колонок)
 	ID_IMG_TABLE_RANGE_DRAW,                          // разбить ячейки карандашом
	ID_IMG_TABLE_EXPRESSION,                          // формула (Fx)
	ID_IMG_TABLE_SUMM,                                // суммирование
	ID_IMG_OPEN_BASE,                                 // открыть из базы стандартных
	ID_IMG_SAVE_BASE,                                 // сохранить в базу стандартных
	ID_IMG_TABLE_PAGES,                               // разбивка таблицы на страницы
	ID_IMG_TABLE_GROUP,                               // группировка и объединение отчёта в таблице

	//ППР (вторая серия)
	ID_IMG_PPR_MANAGER,																//ППР: менеджер проектов
	ID_IMG_PPR_SCOOP,																	//ППР: ковш
	ID_IMG_PPR_BULDOZER,															//ППР: бульдозер
	ID_IMG_PPR_PILEDRIVER,														//ППР: копер
	ID_IMG_PPR_CRANE,																	//ППР: башенный кран
	ID_IMG_PPR_EXCAVATOR,															//ППР: экскаватор

	ID_IMG_HF_AXES,
	ID_IMG_HF_THREAD,
	ID_IMG_HF_Q1,
	ID_IMG_HF_Q2,
	ID_IMG_HF_Q3,
	ID_IMG_HF_Q4,
	ID_IMG_SAVE_AS,																		//Сохранить как

	ID_IMG_FIX_FIELD_JOINT,                           // монтажный шов
	ID_IMG_FIX_SOLDERING,                             // Пайка
	ID_IMG_FIX_GLUING,                                // Склеивание
	ID_IMG_FIX_CLAMPTYPE1,                            // Скобы, тип 1
	ID_IMG_FIX_CLAMPTYPE2,                            // Скобы, тип 2
	ID_IMG_FIX_CROSSLINK,                             // Сшивание
	
	ID_IMG_BF_BOUNDHATCH,                             // Граничная штриховка
	ID_IMG_BF_DASHBAND,                               // Штриховая полоса
	ID_IMG_BF_GROUNDBORDER,                           // Граница грунта
	ID_IMG_BF_HEATISOL,                               // Теплоизоляция
	ID_IMG_BF_WATERISOL,                              // Гидроизоляция
	
	//иконка команды "дополнительные маркеры"
	ID_IMG_SPDS_ADDMARKERS,

	ID_IMG_PT_LINEAR_OBJECT,
	ID_IMG_PT_POINT_OBJECT,

	ID_IMG_STOP,                                       // Стоп (дорожный знак)
	ID_IMG_ATTRIBUTE,                                       // Стоп (дорожный знак)

	//ППР (третья серия)
	ID_IMG_PPR_ADDJOB,																//ППР: лопата с плюсиком
	ID_IMG_PPR_DELJOB,																//ППР: лопата с минусом
	ID_IMG_PPR_SELJOB,																//ППР: лопата с деревом

	ID_IMG_PPR_JOBREP,																//ППР: таблица с лопатой
	ID_IMG_PPR_DEVREP,																//ППР: таблица со стрелой
	ID_IMG_PPR_JOBCALREP,															//ППР: календарь с лопатой
	ID_IMG_PPR_DEVCALREP,															//ППР: календарь со стрелой
	ID_IMG_PPR_WORKCALREP,														//ППР: календарь с человечком

	ID_IMG_PPR_WATERCALC,															//ППР: эпсилон с водопроводным краном
	ID_IMG_PPR_ENERGYCALC,														//ППР: эпсилон с электромолнией

	ID_IMG_PPR_FROMPRJ,																//ППР: дерево со стрелкой наружу
	ID_IMG_PPR_PLUS,																	//ППР: большой красный плюс
	ID_IMG_PPR_MINUS,																	//ППР: большой красный минус

	ID_IMG_PPR_PILE,																	//ППР: красная свая

	ID_IMG_PPR_JOB,																		//ППР: лопата

	ID_IMG_PPR_ADDDEV,																//ППР: стрела с плюсиком
	ID_IMG_PPR_DELDEV,																//ППР: стрела с минусом
	ID_IMG_PPR_PLACEDEV,															//ППР: стрела с форматом

	ID_IMG_PPR_PIPELAYER,															//ППР: трубоукладчик
	ID_IMG_PPR_AUTOLIFT,															//ППР: автоподъемник
	ID_IMG_PPR_DRILL,																	//ППР: буровая машина
	ID_IMG_PPR_AUTOCRANE,															//ППР: автомобильный кран
	ID_IMG_PPR_CATERPILLARCRANE,											//ППР: гусенечный кран
	ID_IMG_PPR_WHEELMOUNTCRANE,												//ППР: пневмоколесный кран

	// иконки для диалога "Проверка поэтажного плана"	
	ID_IMG_OVERLAY_GREEN_CHECK,
	ID_IMG_OVERLAY_READ_CHECK,
	ID_IMG_FLAG_NORMAL,
	ID_IMG_FLAG_WARNING,
	ID_IMG_FLAG_CRITICAL,

//-------------------------------------
//Пятая порция иконок (юбилей, однако)
//-------------------------------------

	//ППР (4я серия)
	ID_IMG_PPR_CMIXER,																//ППР: бетономешалка
	ID_IMG_PPR_CPUMP,																	//ППР: бетононасос
	ID_IMG_PPR_JOB_WCALC,															//ППР: лопата с эпсилон
	ID_IMG_PPR_JOB_WTECH,															//ППР: лопата со стрелой
	ID_IMG_PPR_JOB_WCALCTECH,													//ППР: лопата с эпсилон и стрелой
	ID_IMG_PPR_TRAILER,																//ППР: прицеп
	ID_IMG_PPR_HAULER,																//ППР: тягач
	ID_IMG_PPR_BOARDTRUCK,														//ППР: бортовой грузовик

	ID_IMG_SLOPE_SWAP_EDGE_FOOT,

	//ППР (5я серия)
	ID_IMG_PPR_BUILDINGAREA,													//ППР: площадной объект с лопатой

	ID_IMG_LAYOUT_PARAMETERS,
	ID_IMG_HATCH_PARAMETERS,
	ID_IMG_MAKE_LAYOUT,
	ID_IMG_ADD_PLATE_INTO_LAYOUT,

	ID_IMG_PPR_ROADSIGN,															//ППР: дорожный знак

	ID_IMG_BATCH_ICON,				//картинка от bat файла

	ID_IMG_ROADWAY_HATCH_PARAMETERS,
	ID_IMG_WAYSIDE_HATCH_PARAMETERS,

	//ППР (6я серия)
	ID_IMG_PPR_LAREA,
	ID_IMG_PPR_SAREA,
	ID_IMG_PPR_RAREA,
	ID_IMG_PPR_PAREA,
	ID_IMG_PPR_DZONE,
	ID_IMG_PPR_WZONE,
	ID_IMG_PPR_INVBUILD,
	ID_IMG_PPR_UCBUILD,
	ID_IMG_PPR_EBUILD,
	ID_IMG_PPR_BRBUILD,
	ID_IMG_PPR_SITEM,
	ID_IMG_PPR_WWASH,
	ID_IMG_PPR_ROAD,
	ID_IMG_EYE,                 // глаз (для диалога таблиц)

	ID_IMG_CS_CARTESIAN,
	ID_IMG_CS_POLAR,
	ID_IMG_CS_HOLE_TABLE,
	ID_IMG_CS_LIST_OF_COORD,
	ID_IMG_CS_ADD_HOLE,
	ID_IMG_CS_DEL_HOLE,
	ID_IMG_HL_SHOW_TEXT,
	ID_IMG_HL_SHOW_GRAPHICS,
	ID_IMG_CS_NUMBER,
	ID_IMG_GNB_GRID,						//Сетка ГНБ
	ID_IMG_GNB_TRACE,						//Трасса ГНБ
	ID_IMG_GNB_GROUND,					//Профиль грунта
	ID_IMG_GNB_UL,							//Коммуникация
	ID_IMB_GNB_PIT,							//Котлован
	ID_IMG_CS_DESIGNATION_TABLE,
	
	ID_IMB_PPR_SLOPE,
	ID_IMB_PPR_ROADCROSS,
	ID_IMG_PPR_ROADSECTION,
	ID_IMB_PPR_LINEAROBJECT,
	ID_IMB_PPR_POINTOBJECT,

	// Режимы вписывания текста в ячейку (для диалога таблиц)
	ID_IMG_FIT_NONE,            // не вписывать
	ID_IMG_HFIT_WRAP,           // переносить по словам
	ID_IMG_HFIT_SHRINK,         // сжать текст по горизонтали
	ID_IMG_VFIT_EXPAND,         // увеличить высоту строки
	ID_IMG_VFIT_SHRINK,         // уменьшить высоту текста
	ID_IMG_VFIT_ADD,            // добавить виртуальные строки

	ID_IMG_FORMAT_TITLE,        // титульные листы и обложки

	ID_IMG_HL_CREATE_DIM,       // Создать размер на отверстии
	ID_IMG_NO_ASSOCIATION,      // отключенная ассоциативность (пара для ID_IMG_ASSOCIATION)

	ID_IMG_PT_EMBEDDINGTYPE,	// ПланКАД::Разрывы::Тип встраивания разрыва на дугу

	ID_IMG_ENT_NOTE,	        	// Универсальная выноска

	ID_IMG_RF_BAR,              // Арматурный пруток
	ID_IMG_RF_ASSEMBLY,         // Сборка (арматурная)
	ID_IMG_RF_CLAMP,            // Арматурный хомут
	ID_IMG_RF_CLAW,             // Арматурная скоба
	ID_IMG_RF_DISTRIBUTION,     // Распределение (арматуры)
	ID_IMG_RF_DOT,              // Сечение арматуры
	ID_IMG_RF_FRAME,            // Арматурный каркас
	ID_IMG_RF_GRID,             // Арматурная сетка
	ID_IMG_RF_STUD,             // Арматурная шпилька
	ID_IMG_RF_CONSTRUCTION,     // Конструкция (железобетонная)
	ID_IMG_RF_VARIANT,          // Вариант конструкции (железобетонной)
	ID_IMG_RF_ELEMENT,          // Конструктивный элемент
	ID_IMG_RF_BLOCK,            // Конструктивный блок
	ID_IMG_RF_PRODUCT_SPEC,     // Спецификация на арматурное изделие
	ID_IMG_RF_STEEL_SHEET,      // Ведомость расхода стали
	
	ID_IMG_DWG,                 // Иконка файла dwg

	ID_IMG_PPR_NONINVBUILD,     // Неинвентарное здание
	ID_IMG_PPR_PROJECTEDBUILD,  // Проектируемое здание

	ID_IMG_WALL_REVERT,         // Перевернуть стену
	ID_IMG_WALL_MATERIALS,      // Материалы стен

	ID_IMG_WIND_ROSE,           // Роза ветров
	ID_IMG_NORTH_DIR,           // Направление на север
	
	ID_IMG_PPR_RATE,			// Расценка
	ID_IMG_PPR_TECHNICS,		// Техника
	ID_IMG_PPR_PERSONAL,		// Персонал
	ID_IMG_PPR_MATERIAL,		// Материал
	ID_IMG_PPR_ERASE,			// Удаление

	ID_IMG_CHAMFER_CUTMODE_1,	// Фаска с полным отсечением
	ID_IMG_CHAMFER_CUTMODE_2,	// Фаска с частичным отсечением
	ID_IMG_CHAMFER_CUTMODE_3,	// Фаска без отсечения
	ID_IMG_FILLET_CUTMODE_1,	// Сопряжение с полным отсечением
	ID_IMG_FILLET_CUTMODE_2,	// Сопряжение с частичным отсечением
	ID_IMG_FILLET_CUTMODE_3,	// Сопряжение без отсечения
	ID_IMG_FILLET_EXT_DIM,		// Сопряжение с дополнительным образмериванием
	ID_IMG_CHAMFER_ONE_LENGTH,	// Фаска симметричная. Длина1
	ID_IMG_CHAMFER_TWO_LENGTHS,	// Фаска несимметричная. Длина1 + Длина2
	ID_IMG_CHAMFER_LENGTH_CORNER,// Фаска несимметричная. Длина + Угол
	ID_IMG_FILLET_AS_CIRCLE,	// Сопряжение в виде касательной окружности
	ID_IMG_ROAD_WIDENING,		// Площадки уширения/разворота
	ID_IMG_TOL_F, // Non-rigid part
	ID_IMG_TOL_L, // Least material requirement

	ID_IMG_RF_EMBEDDED,          // Закладное изделие
	ID_IMG_RF_METAL_ROLLING,     // Металлопрокат

	ID_IMG_PPR_EXPLANATORY_NOTE, // Пояснительная записка
	ID_IMG_PPR_CONSTRUCTIONS_EXPLICATION, // Экспликация зданий и сооружений
	ID_IMG_PPR_TEMP_BUILDING_EXPLICATION, // Экспликация временных зданий
	ID_IMG_PPR_EXPORT,           // Экспорт проекта

	ID_IMG_RF_SLAVEVIEW,         // Условный вид
	
	ID_IMG_PPR_ADD_MAT,			// Добавить материал
	ID_IMG_PPR_DEL_MAT,			// Удалить материал
	ID_IMG_PPR_PLACE_MAT,		// Разместить материал на чертежа
	ID_IMG_PPR_MAT,				// Материал
	ID_IMG_PPR_MAT_IN_DOC,		// Материал на чертеже
	ID_IMG_PPR_STORAGE_CALC,	// Расчёт площади складирования

	ID_IMG_NOTE_MULTILINE, // Многострочная выноска

	ID_IMG_USE_3D_MODELS_4STD, // Использовать 3d модели для вставки стандартных

	// стрелки размеров
	ID_IMG_ARROW_ARCHTICK,
	ID_IMG_ARROW_OPEN30,
	ID_IMG_ARROW_SMALL,
	ID_IMG_ARROW_DOTSMALL,
	ID_IMG_ARROW_ORIGIN,
	ID_IMG_ARROW_ORIGIN2,
	ID_IMG_ARROW_CLOSED,
	ID_IMG_ARROW_BOXFILLED,
	ID_IMG_ARROW_BOXBLANK,
	ID_IMG_ARROW_INTEGRAL,

	ID_IMG_NET_EQUIPMENT,		// Инженерные сети: оборудование
	ID_IMG_NET_PORT,			// Инженерные сети: коннектор
	ID_IMG_NET_TRACE,			// Инженерные сети: трасса

	ID_IMG_DECREASE_INDENT,		// ТТ. Уменьшить отступ 
	ID_IMG_INCREASE_INDENT,		// ТТ. Увеличить отступ
	ID_IMG_LINE_SPACING,		// ТТ. Межстрочный интервал
	ID_IMG_LEFT_ALIGNMENT,		// ТТ. По левому краю
	ID_IMG_CENTER_ALIGNMENT,	// ТТ. По центру
	ID_IMG_RIGHT_ALIGNMENT,		// ТТ. По правому краю
	ID_IMG_JUSTIFY_ALIGNMENT,	// ТТ. По ширине

	ID_IMG_NET_PORTTABLE,		// Инженерные сети: таблица соединений

	ID_IMG_VS_ROTATED2,
	ID_IMG_SYM_RUBLE,
	ID_IMG_SYM_UP,
	ID_IMG_SYM_DOWN,
	ID_IMG_FILLET_AS_ARC,		// Сопряжение в виде дуги (обычное)
	
	IMG_PARAGRAPH_UP,  ///  ТТ. Переместить параграф вверх
	IMG_PARAGRAPH_DOWN, ///  ТТ. Переместить параграф вниз
	IMG_FILL_FROM_MCWORD, ///  ТТ. Заполнить из MC Word

	ID_IMG_TEXT_FIT,
	ID_IMG_WALL,
	ID_IMG_WINDOW,
	ID_IMG_DOOR,
	ID_IMG_COLUMN,
	ID_IMG_STAIR,
	ID_IMG_WALLOBJECT,
	ID_IMG_SLAB,
	ID_IMG_SLAB_CROSS_SECTION,
	ID_IMG_ARCH_MATERIALS,	// Архитектурный материал
	ID_IMG_FILLET_AS_HOLLOW_CHAMFER,		// Неполное сопряжение (галтель)
	ID_IMG_ENT_WELD_HIDDEN_BASE_LINE,		// Сварной шов без базовой линии

	//ППР+
	ID_IMG_PPR_MOTOR_GRADER,				//ППР: автогрейдер
	ID_IMG_PPR_ASPHALT_PAVER,				//ППР: асфальтоукладчик
	ID_IMG_PPR_ROAD_ROLLER,					//ППР: каток
	ID_IMG_PPR_LOADER,						//ППР: погрузчик

	ID_IMG_SCHEDULE,

	ID_IMG_TT_NOTEBOOK_LAST_USED,			//ТТ: Записная книжка, последние использованные

	ID_IMG_PARAMTABLE,						//Библиотека атрибутов: таблица параметров

	ID_IMG_PPR_CALENDAR,					//ППР: Диаграмма Гантта- Управление календарями
	ID_IMG_PPR_DIPPER,						//ППР: ковш
	ID_IMG_PPR_GNB,							//ППР: установки ГНБ

	ID_IMG_METAL17,// Уголок равнополочный
	ID_IMG_METAL18,// Труба круглая
	ID_IMG_METAL19,// Тавр
	ID_IMG_METAL20,// Лист
	ID_IMG_METAL21,// Прямоугольное сечение из двух уголков

	ID_IMG_ARC_AXIS,						// СПДС Дуговая ось
	ID_IMG_CIRC_AXIS,						// СПДС Круговая ось
	ID_IMG_ROOF,

	ID_IMG_CHAMFER_ADDLINES,				//Диалог фаски. Дополнительные линии

	ID_IMG_ARCHITECTURE_SETSTYLE,			// Панель менеджера проекта Архитектура. Назначить стиль объекту
	ID_IMG_NOTE_FRAME,						// Рамка вокруг второго поля выноски

	ID_IMG_PPR_CALC_WORKFORCE,				// Расчеты ППР: кадры
	ID_IMG_PPR_CALC_TEMP_BUILDINGS,			// Расчеты ППР: временные здания
	ID_IMG_PPR_CALC_COMPRESSED_AIR,			// Расчеты ППР: сжатый воздух
	ID_IMG_PPR_CRANE_HOOK,					// ППР: крюк крана

	ID_IMG_EYE1,							// IFC Viewer: показать/скрыть только это
	ID_IMG_IFC_EXPORT,						// СПДС Архитектура: экспорт в IFC
	ID_IMG_IFC_IMPORT,						// СПДС Архитектура: импорт из IFC

	ID_IMG_SPECIFY_POINT,					// Указать точку на чертеже.
	ID_IMG_NUM_METHOD_LTR_TTB,				// [LeftToRightTopToBottom]. Способ нумерации объектов "Слева направо, сверху вниз".
	ID_IMG_NUM_METHOD_RTL_TTB,				// [RightToLeftTopToBottom]. Способ нумерации объектов "Справа налево, сверху вниз".
	ID_IMG_NUM_METHOD_BTT_LTR,				// [BottomToTopLeftToRight]. Способ нумерации объектов "Снизу вверх, слева направо".
	ID_IMG_NUM_METHOD_BTT_RTL,				// [BottomToTopRightToLeft]. Способ нумерации объектов "Снизу вверх, справа налево".
	ID_IMG_NUM_METHOD_RADIAL_CW,			// [RadialClockwise]. Способ нумерации объектов "Круговой по часовой стрелке".
	ID_IMG_NUM_METHOD_RADIAL_ACW,			// [RadialAnticlockwise]. Способ нумерации объектов "Круговой против часовой стрелки".
	ID_IMG_NUM_METHOD_SPIRAL_CW_TC,			// [SpiralClockwiseToCenter]. Способ нумерации объектов "Спиральный по часовой стрелке к центру".
	ID_IMG_NUM_METHOD_SPIRAL_ACW_FC,		// [SpiralAnticlockwiseFromCenter]. Способ нумерации объектов "Спиральный против часовой стрелки от центра".

	ID_IMG_REPLACE_ME,						// Временное изображение, которое нужно заменить на что-то адекватное.
	ID_IMG_TOL_ADDLEADER,// Добавить линию-выноску
	ID_IMG_NOTE_LASTLINE,// Последняя строка многострочной выноски без полки

	ID_IMG_TABLE_ROW_DELETE,				// Таблицы: удалить строку
	ID_IMG_TABLE_ROW_ADD_BEFORE,			// Таблицы: добавить строку до
	ID_IMG_TABLE_ROW_ADD_AFTER,				// Таблицы: добавить строку после
	ID_IMG_TABLE_COLUMN_DELETE,				// Таблицы: удалить столбец
	ID_IMG_TABLE_COLUMN_ADD_BEFORE,			// Таблицы: добавить столбец до
	ID_IMG_TABLE_COLUMN_ADD_AFTER,			// Таблицы: добавить столбец после
	ID_IMG_TOL_U,

	ID_IMG_PARKING_PLACE,

	ID_IMG_CS_CARTESIAN_LEFT,				// Декартова левая система координат(ось Y вверх, ось X влево)
	ID_IMG_PPR_MATERIAL_CALCREP,			// ППР: календарь с кирпичами
	ID_IMG_PPR_OBJECTS_READY,				// ППР: готовность объектов
	ID_IMG_BIM_LINK_ONJECT,					// ППР: Создание связи IFC-объекта с работой
	ID_IMG_BIM_REMOVE_LINK,					// ППР: Разорвать связь IFC-объекта с работой

	ID_IMG_QS_FROZEN_LAYERS,				// Быстрый выбор: Учитывать замороженные и скрытые слои

// При добавлении необходимо продублировать в аналогичный список в Core\Src\mapimngd\ApplicationServices.h

//*************************************************************************************************************************************************************
// До этого места шли индексы обычных иконок, хранящихся в ресурсах
//	MechCtl\res\global*.bmp		(обычное состояние)
//	MechCtl\res\globalDis*.bmp	(запрещенное (серое) состояние)
//
// С этого места начинаются локализованные иконки, которые в зависимости от установленного языка приложения подгружаются из
//	MechaniCS\Core\Bin\DataRO\ru-RU\ImageList.bmp
//	MechaniCS\Core\Bin\DataRO\en-EN\ImageList.bmp
//	MechaniCS\Core\Bin\DataRO\es-ES\ImageList.bmp
// BMP-файлы с локализованными иконками содержат сразу обычные и запрещенные изображения.
// 
// По завершении загрузки все иконки собираются в один глобальный ImageList и имеют порядковый номер, заданный в этом списке.
//*************************************************************************************************************************************************************
	ID_IMG_TECHREQ,				// Технические требования
	ID_IMG_OPEN_TT,				// Открыть ТТ
	ID_IMG_SAVE_TT,				// Сохранить ТТ
	ID_IMG_TRANSMIT_TT,			// Передать в ТТ
	ID_IMG_SORT,				// Сортировать выноски
	ID_IMG_SORT_ACS,			// Сортировать по возрастанию
	ID_IMG_SORT_DESC,			// Сортировать по убыванию
	ID_IMG_BOLD,				// ТТ. Жирный
	ID_IMG_ITALIC,				// ТТ. Курсив
	ID_IMG_UNDERLINE,			// ТТ. Подчеркнутый
	ID_IMG_SIMPLE_NUMERATION,	// ТТ. Простая нумерация
	ID_IMG_MULTI_NUMERATION,	// ТТ. Сложная нумерация
	ID_IMG_TP,					// Иконка технических характеристик
	ID_IMG_STRIKEOUT			// ТТ. Зачеркнутый текст
};

#define ID_IMG_ALIGN_MIDDLELEFT   ID_IMG_ALIGN_LEFT
#define ID_IMG_ALIGN_MIDDLERIGHT  ID_IMG_ALIGN_RIGHT
#define ID_IMG_ALIGN_TOPCENTER    ID_IMG_ALIGN_TOP
#define ID_IMG_ALIGN_MIDDLECENTER ID_IMG_ALIGN_MIDDLE
#define ID_IMG_ALIGN_BOTTOMCENTER ID_IMG_ALIGN_BOTTOM

_inline int arrowToImgIndex(int arrow){
	switch (arrow) {
		case MCS_ArrNone:         return ID_IMG_ARROW_NONE;
		case MCS_ArrArrow:        return ID_IMG_ARROW_ARROW;
		case MCS_ArrDot:          return ID_IMG_ARROW_DOT;
		case MCS_ArrOblique:      return ID_IMG_ARROW_OBLIQUE;
		case MCS_ArrDatumFilled:  return ID_IMG_ARROW_BASE;
		case MCS_ArrOpen:         return ID_IMG_ARROW_OPEN;
		case MCS_ArrHalf:         return ID_IMG_ARROW_HALF;
		case MCS_ArrOpen90:       return ID_IMG_ARROW_OPEN90;
		case MCS_ArrInverseHalf:  return ID_IMG_ARROW_INVERSE_HALF;
		case MCS_ArrClosedBlank:  return ID_IMG_ARROW_CLOSED_BLANK;
		case MCS_ArrDatumBlank:   return ID_IMG_ARROW_BASE_BLANK;
		case MCS_ArrDotBlank:     return ID_IMG_ARROW_DOT_BLANK;
		case MCS_ArrArchTick:     return ID_IMG_ARROW_ARCHTICK;
		case MCS_ArrOpen30:       return ID_IMG_ARROW_OPEN30;
		case MCS_ArrSmall:        return ID_IMG_ARROW_SMALL;
		case MCS_ArrDotsmall:     return ID_IMG_ARROW_DOTSMALL;
		case MCS_ArrOrigin:       return ID_IMG_ARROW_ORIGIN;
		case MCS_ArrOrigin2:      return ID_IMG_ARROW_ORIGIN2;
		case MCS_ArrClosed:       return ID_IMG_ARROW_CLOSED;
		case MCS_ArrBoxFilled:    return ID_IMG_ARROW_BOXFILLED;
		case MCS_ArrBoxBlank:     return ID_IMG_ARROW_BOXBLANK;
		case MCS_ArrIntegral:     return ID_IMG_ARROW_INTEGRAL;
		case MCS_ArrThickLine:    return ID_IMG_ARROW_THICK_LINE;
		default:                  break;;
	}
	return ID_IMG_ARROW_UNKNOWN;
}

//////////////////////////////////////////////////////////////////////////
//Для тех кто не пользует MFC
//=============================================================================

extern "C" MECHCTL_API HIMAGELIST GetCommonImageList16x16();
extern "C" MECHCTL_API HIMAGELIST GetCommonImageListDisabled16x16();

//---------------------------------------------------------------------------
namespace MSXML2
{
	struct IXMLDOMElement;
};

//=============================================================================
// Пересчет размеров контролов при системном масштабе текстов > 100%
//=============================================================================
#define DEF_DPI 96
struct McLogPix
{
	int m_lpixX;
	int m_lpixY;

	McLogPix()
	{
		m_lpixX = DEF_DPI;
		m_lpixY = DEF_DPI;
	}

	McLogPix(HWND hwnd)
	{
		m_lpixX = DEF_DPI;
		m_lpixY = DEF_DPI;
		if (hwnd)
			Init(hwnd);
	}

	void Init(HWND hwnd)
	{
		HDC hdc = GetWindowDC(hwnd);
		m_lpixX = GetDeviceCaps(hdc, LOGPIXELSX);
		m_lpixY = GetDeviceCaps(hdc, LOGPIXELSY);
		ReleaseDC(hwnd, hdc);
	}

	int Log2Pix(int n) { return MulDiv(n, m_lpixX, DEF_DPI); }
	int Pix2Log(int n) { return MulDiv(n, DEF_DPI, m_lpixX); }
};
//=============================================================================

#ifndef MECHCTL_NO_FMC

#include "NetInteract.h"

// AGL: начиная с VS2012 MFC не поддерживает загрузку truecolor-битмапов на тулбары.
// Поэтому загрузку надо звать явно через этот метод
#if _MSC_VER >= 1700
	BOOL MECHCTL_API mcsLoadToolbar(CToolBar* pTB, UINT nIDResource);
#else
	__inline BOOL mcsLoadToolbar(CToolBar* pTB, UINT nIDResource) {
		return pTB->LoadToolBar(nIDResource);
	}
#endif

__inline BOOL mcsLoadToolbar(CToolBar& TB, UINT nIDResource) {
	return mcsLoadToolbar(&TB, nIDResource);
}

//=============================================================================
//InputText
class MECHCTL_API CxInputTextWnd
{
public:
	CxInputTextWnd();
	McsString strValue;
	HRESULT getText(LPCTSTR strPromt, LPCTSTR strCaption = NULL, HWND parent = NULL, LPCTSTR strHelpID = NULL);
};

inline HRESULT CxInputText(McsString& strOut, LPCTSTR strPromt, LPCTSTR strCaption = NULL, HWND parent = NULL, LPCTSTR strHelpID = NULL)
{
	CxInputTextWnd input;
	input.strValue = strOut;
	HRESULT hRes = input.getText(strPromt, strCaption, parent, strHelpID);
	if(hRes == S_OK){
		strOut = input.strValue;
	}
	return hRes;
}

//////////////////////////////////////////
//----------------------------------------
// Scale ctrl
//----------------------------------------
// имя класса окна
#define MCS_SCALE_CLASSNAME "MCS_SCALE"

// событие, посылаемое при изменении масштаба; wParam - указатель на double; 
// rScale = *(double*)wParam;
// если это событие послать в окно контрола - будет проициализирован контрол; wParam = (WPARAM)&rScale;
#define WM_MCSSCALE WM_USER+20

// убрать/поставить картинку с лупой (wParam == 0 - убрать иначе поставить) 
#define WM_MCSSCALE_IMAGE WM_USER+21
// энейбл/дисейбл кнопки масштаба (wParam == 0 - задисейблить)
#define WM_MCSSCALE_ENABLE WM_USER+22

__inline BOOL SimpleToolbar(CWnd* pThis, CToolBar& tb, int idc, UINT idr, BOOL fVertical = FALSE)
{
	CWnd* pSocketWnd = pThis->GetDlgItem(idc);
	if (pSocketWnd == NULL) return FALSE;
	CRect rcSocket;
	pSocketWnd->GetClientRect(&rcSocket);

	if (!tb.CreateEx(pSocketWnd, TBSTYLE_FLAT | TBSTYLE_TOOLTIPS , WS_CHILD | WS_VISIBLE | CBRS_SIZE_FIXED | CBRS_ALIGN_TOP  , CRect(0, 0, 0, 0), idr))
					return FALSE;

	if (!mcsLoadToolbar(tb, idr))
		return FALSE;

	if (fVertical) {
					int nCount = tb.GetToolBarCtrl().GetButtonCount();
					for (int i=0; i<nCount; i++) {
									UINT nStyle = tb.GetButtonStyle(i);
									nStyle |= TBBS_WRAPPED;
									tb.SetButtonStyle(i, nStyle);
					}
	}

	CSize szToolBar = tb.CalcFixedLayout(FALSE, FALSE);
	pSocketWnd->SetWindowPos(NULL, 0, 0, szToolBar.cx, szToolBar.cy, SWP_NOMOVE);
	tb.MoveWindow(&CRect(CPoint(0, 0), szToolBar), TRUE);
	tb.SetOwner(pThis);

	CRect rc;
	tb.GetWindowRect(&rc);
	pThis->GetDlgItem(idc)->ScreenToClient(rc);
	tb.MoveWindow(rc);
	tb.GetWindowRect(&rc);
	pThis->ScreenToClient(rc);
	pThis->GetDlgItem(idc)->MoveWindow(rc);
	return TRUE;
}
//=============================================================================
#define MCS_STDCTLS_MARGIN_SMALL        2 
#define MCS_STDCTLS_MARGIN_NORMAL       4 
 
#define MCS_STDCTLS_BUTTONS_SMALL_X     35 
#define MCS_STDCTLS_BUTTONS_SMALL_Y     15 
 
#define MCS_STDCTLS_BUTTONS_NORMAL_X    48 
#define MCS_STDCTLS_BUTTONS_NORMAL_Y    15 

__inline void StandardizeControl( CWnd* pWnd, bool bSmallBtn = TRUE, UINT idLeftBtmControl = 0, UINT idOkBtn = IDOK, UINT idCancelBtn = IDCANCEL ) {
                           
	UINT sz[3] = { MCS_STDCTLS_BUTTONS_SMALL_X, MCS_STDCTLS_BUTTONS_SMALL_Y, MCS_STDCTLS_MARGIN_SMALL }; 
	if( bSmallBtn == false ) {
					sz[0] = MCS_STDCTLS_BUTTONS_NORMAL_X;
					sz[1] = MCS_STDCTLS_BUTTONS_NORMAL_Y;
					sz[2] = MCS_STDCTLS_MARGIN_NORMAL;
	}

	CRect rcCtrl, rcThis;

	rcCtrl.left             =       sz[2];
	rcCtrl.right    =       sz[0];
	rcCtrl.top              =       sz[1];
	rcCtrl.bottom   =       sz[1];
	if( MapDialogRect(pWnd->m_hWnd, rcCtrl) != 0 ) {
					sz[0] = rcCtrl.right;
					sz[1] = rcCtrl.top;
					sz[2] = rcCtrl.left;    
	}


	pWnd->GetClientRect(&rcThis);
	if( idLeftBtmControl!=0 ) {
					CWnd* pCtrl = pWnd->GetDlgItem(idLeftBtmControl);
					if(pCtrl){
									pCtrl->GetClientRect(&rcCtrl);
									int dh = rcCtrl.Height();
									rcCtrl.left+=sz[2]; rcCtrl.right+=sz[2];
									rcCtrl.bottom = rcThis.bottom - sz[2];
									rcCtrl.top = rcCtrl.bottom - dh;
									pCtrl->MoveWindow(rcCtrl);
					}
	}

	rcCtrl.bottom   = rcThis.bottom - sz[2];
	rcCtrl.top              = rcCtrl.bottom - sz[1];
	rcCtrl.right    = rcThis.right - sz[2];
	rcCtrl.left             = rcCtrl.right - sz[0];
	CWnd *pBtn1 = NULL, *pBtn2 = NULL; 
	if( idCancelBtn!=0 ) {
					pBtn1 = pWnd->GetDlgItem(idCancelBtn);
					if( pBtn1 ) {
									pBtn1->MoveWindow(rcCtrl, FALSE);                               
									rcCtrl.right = rcCtrl.left - sz[2];
					}
	}

	if( idOkBtn!=0 ) {
					pBtn2 = pWnd->GetDlgItem(idOkBtn);
					if( pBtn2 ) {
									rcCtrl.left     = rcCtrl.right - sz[0];
									pBtn2->MoveWindow(rcCtrl);                              
					}
	}
	if(pBtn1) pBtn1->Invalidate();
	if(pBtn2) pBtn2->Invalidate();
}
//=============================================================================

//////////////////////////////////////////////////////////////////////////
///Cx Controls
//////////////////////////////////////////////////////////////////////////
// Define section
//

// см. SetTextFormat
#define BTN_TEXT_SIMPLE         0x00
#define BTN_CENTER                      0x00
#define BTN_LEFT                        0x01
#define BTN_RIGHT                       0x02
#define BTN_TEXT_BOLD           0x04
#define BTN_TEXT_ITALIC         0x08
#define BTN_TEXT_UNDERLINE      0x10
#define BTN_TEXT_STRIKEOUT      0x20

#define DLG_DELTA                       4

////
//
#define INBTN_OFFSET    4
#define ARROW_SIZE              6

#ifndef WM_HOST_KEEP_FOCUS
	#define WM_HOST_KEEP_FOCUS (WM_USER + 0x6D01)
#endif
#ifndef HOST_KILL_FOCUS
	#define HOST_KILL_FOCUS 100// Передать фокус в документ
#endif
#define HOST_KEEP_FOCUS 1// Не передавать фокус в документ
#define HOST_AUTO_FOCUS 0// Решение о передаче фокуса остаётся за платформой. Корректно работает для C++.

//////////////////////////////////////////////////////////////////////////
class MECHCTL_API CxDialog : public CDialog
{
public:
	CxDialog( UINT nIDTemplate, CWnd* pParentWnd = NULL );
	virtual bool BeginEditorCommand();	
	virtual bool CompleteEditorCommand();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	virtual bool OnHelpCall();
	virtual bool OnExitSizeMoving(){return false;};
	LPCTSTR m_iHelpId;
	HINSTANCE m_hinstance;
	DWORD m_dwFlags;
};

//////////////////////////////////////////
// CxButtonLt - custom button
class MECHCTL_API CxButtonLt : public CButton
{
public:
	CxButtonLt();
	virtual ~CxButtonLt();
	BOOL Create(CWnd* pParent, const RECT& rect, DWORD nCtrlID, DWORD AdditionalStyles = 0);
	//Стандартные кнопки - IDOK, IDCANCEL, ID_HELP, ID_APPLY_NOW
	//Если создаете с кнопкой ID_APPLY_NOW iMode ставить в 1
	BOOL CreateStdButton(CWnd* pParent, DWORD nCtrlID, int iMode = 0);
	void RecalcButton();
	void SetState( BOOL bHighlight ) { m_bHighlight = bHighlight; RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW); }
	BOOL GetState() { return m_bHighlight; }

	// разрешить устанавливать фокус
	void SetNoFocus(BOOL fNoFocus = TRUE) { m_fNoFocus = fNoFocus; } 
	// утановить окно, которое будет принимать сообщения
	void SetOwner(CWnd* pOwner) { m_pOwner = pOwner; } 
	// разрешить устанавливать фокус
	void SetShadowColor(COLORREF colorShadow) { m_colorShadow = colorShadow; } 
	// цвет фона
	void SetFaceColor(COLORREF colorFace) { m_colorFace = colorFace; } 
	// цвет текста кнопки
	void SetTextColor(COLORREF colorText) { m_colorText = colorText; } 
	// формат текста кнопки
	void SetTextFormat(UINT uiTextFormat = BTN_TEXT_SIMPLE) { m_uiTextFormat = uiTextFormat; }
	// установить image из предопределенного набора
	UINT GetImage() { return m_nImage; }
	void SetImage(UINT nImage);
	// установить текст
	void SetText(LPCTSTR strText) { SetWindowText(strText); }
	// сделать кнопку плоской
	void SetFlat(BOOL fFlat = TRUE) { m_fFlat = fFlat; }
	// дорисовать стрелочку
	void SetArrow(BOOL fArrow = TRUE, BOOL bDownArrow = TRUE) { m_fArrow = fArrow; m_fArrowDown = bDownArrow; }
	// связать с контролом (если cx<0 то cx = height)
	void BindWithControl(DWORD nCtrlID, int side = BTN_RIGHT, int offset = 4, int cx = -1);
	// выставить ширину кнопки в зависимости от длины текста
	void AutoSize(BOOL bWidthOnly = TRUE);

	BOOL IsFlat() { return m_fFlat; }
	BOOL IsArrow() { return m_fArrow; }

	void SetImageList(CImageList *pImageList) { m_pImageList = pImageList; }

	CImageList *GetImageList() { return m_pImageList; }

	protected:
	BOOL getStdButtonRect(CRect& rect);
	CFont* getTextFont();

	protected:
	BOOL m_fNoFocus;
	CWnd* m_pOwner;
	COLORREF m_colorShadow;
	COLORREF m_colorFace;
	COLORREF m_colorText;
	UINT     m_uiTextFormat;
	UINT m_nImage;
	BOOL m_fFlat;
	BOOL m_fArrow;
	BOOL m_fArrowDown;
	BOOL m_fMouseOver;
	BOOL m_bHighlight;

	DWORD m_nBindCtrlID;
	int m_nBindSide;
	int m_nBindOffset;
	int m_nBindCX;
	int m_iStdMode;

	CImageList *m_pImageList;

public:
		//{{AFX_VIRTUAL(CxButtonLt)
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CxButtonLt)
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
//Mechanics Toolbar
class MECHCTL_API CxToolBar : public CToolBar
{
public:
	CxToolBar();
	~CxToolBar();
	CImageList* SetImageList(CImageList *pImgList); //by default seted on gCommonImgList16x16 and return NULL first time
	bool Create(CWnd *pParent, LPRECT rect, UINT idToolbar = AFX_IDW_TOOLBAR, bool bUseText = false);
	bool Create(CWnd *pParent, int idc, UINT idToolbar = AFX_IDW_TOOLBAR, bool bUseText = false);
	bool LoadIDR(int idr, COLORREF mask,int idbDisabled = NULL, COLORREF maskDisabled = NULL);
	bool AddButton(UINT idCommand, int iBmpIndex, LPCTSTR str = NULL, UINT nAdditionalStyle = 0);
	bool AddCheckBox(UINT idCommand, int iBmpIndex, LPCTSTR str = NULL, UINT nAdditionalStyle = 0);
	bool AddCheckGroup(UINT idCommand, int iBmpIndex, LPCTSTR str = NULL, UINT nAdditionalStyle = 0);
	bool AddSeparator();
	bool UpdatePosition(int iColumn = 0); //0 - Auto
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );
	//////////////////////////////////////////////////////////////////////////
	//helper
	bool SetButtonImage(UINT idCommand, int iBmpIndex);//for runtime change image
	int GetButtonImage(UINT idCommand);//for runtime get image index
	BOOL OnToolTipText(UINT ID, NMHDR *pNMHDR, LRESULT *pResult);
	//////////////////////////////////////////////////////////////////////////
	bool AddLeftBottomButons(UINT idOptions,UINT idGost,UINT idHelp = ID_HELP,UINT idMatch = 0);
	HINSTANCE m_hinstance;

	bool AutoScaleButtons();


protected:
	CWnd *m_pParent;        
	int m_idc, m_icount;
	bool m_bUseText;
	RECT m_rect;
	SIZE m_bmpSize;
	CImageList *m_pImgList;
	CImageList *m_pImgListDis;
	DECLARE_MESSAGE_MAP()

	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
		//YAL::WINEFIX - waiting for fix over separfator width
		LRESULT resault = __super::DefWindowProc(message, wParam, lParam);
		if (message == TB_GETBUTTON) {
			TBBUTTON* pButton = (TBBUTTON*)(lParam);
			if (pButton->fsStyle == BTNS_SEP && (pButton->iBitmap == 0 || pButton->iBitmap == -1))
			{
				static int nsep_width = 8;
				pButton->iBitmap = nsep_width;
			}

		}
		return resault;
	}

};

//////////////////////////////////////////////////////////////////////////
//CxMenu
//для удобного создания контекстных меню с картинками
class MECHCTL_API CxMenu : public CMenu
{
public:
	CxMenu();
	CxMenu(HINSTANCE hinstance);
	~CxMenu();
	//iSrtingID - id строки, грузится из dll Установленой в m_hinstance
	//iBmpIndex - индекс картинки в глобальном имаджлисте
	//if(iComadID == UNDEFINED) iComadID = iSrtingID;
	bool AppendMenu(int iStringID, int iBmpIndex, int iComadID = UNDEFINED_IDX, int iFlag = MF_ENABLED, int iBmpChecked = UNDEFINED_IDX);
	void AppendMenu(UINT nCmd, LPCTSTR lpszString, int nImage = UNDEFINED_IDX, UINT nFlags = MF_ENABLED);
	int TrackPopupMenu(CPoint pnt, HWND hwnd);//TPM_RETURNCMD

	//для вызова штатного метода, иначе компилятор что то парится	
	BOOL AppendMenu(UINT nFlags, UINT_PTR nIDNewItem = 0,	LPCTSTR lpszNewItem = NULL){
		return CMenu::AppendMenu(nFlags,nIDNewItem,	lpszNewItem);
	};
	void AppendSeparator(){
		CMenu::AppendMenu(MF_SEPARATOR,-1);
	}
	void SetImageList(CImageList* pImageList){
		m_pImgList = pImageList;
	}

	//устанавливает картинку на пункт меню nIDItem,
	//просматривает также все имеющиеся подменю(!)	
	bool SetMenuItemImage(UINT nIDItem, int nImage);	

	HINSTANCE m_hinstance;
protected:
	CImageList *m_pImgList;
	McsArray<CBitmap *, CBitmap *> m_images;
};

/////////////////////////////////////////////////////////////////////////////
// Аналог popup menu
// Закрывается при потере фокуса (вернет ID_CANCEL)
// или при получении любого WM_COMMAND (вернет ID команды)
class MECHCTL_API CxPopup : public CWnd
{
public:
	enum BorderEnum { brThin = WS_BORDER, brDialog = WS_DLGFRAME, brResize = WS_THICKFRAME };
	CxPopup(CWnd* pParent = NULL, BorderEnum Border = brDialog);
	void EnableReturnKey(bool bEnable = true) { m_bEnableReturnKey = bEnable; }

public:
	// На время работы CxPopup он ставится парентом окну pContent.
	// Перед выходом из Track восстанавливается стары парент.
	// То есть можно один раз создать pContent невидимым, и передавать его в Track
	int Track(int x, int y, CWnd* pContent);
	// Для меню, выпадающего из кнопки. rcPosition - габариты кнопки.
	// Окно появляется так, чтобы его не обрезали края экрана, и чтобы оно не заговаживало кнопку
	int Track(CRect& rcPosition, CWnd* pContent);
	// То же самое, только показывает набор кнопок с указанным текстом.
	// Вернет индекс строки или -1, если ничего не выбрано
	int Track(int x, int y, const mcsStringArray& strCommands);
	int Track(CRect& rcPosition, const mcsStringArray& strCommands);

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	BOOL OnTooltip(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()

	HWND GetRootWindow(HWND hWindow);
	void RunMyModalLoop();
	BOOL AttachContentWindow(CWnd* pContent);
	BOOL DetachContentWindow();

protected:
	int m_idRes;
	CWnd* m_pContent;
	bool m_bEnableReturnKey;
public:
	McsString m_stHelp;
};


BOOL WindowAnimate(HWND hWindow, BOOL bShow);


//////////////////////////////////////////////////////////////////////////
// Пример использования
/*
	CToolBar m_tbMain;
	// ...
	CRect rcButton;
	m_tbMain.GetItemRect(12, &rcButton);
	m_tbMain.ClientToScreen(&rcButton);
	CxPopup menu(this);
	CToolBar tb;
	tb.CreateEx(&menu, TBSTYLE_FLAT|TBSTYLE_TOOLTIPS, WS_CHILD|CBRS_SIZE_FIXED|CBRS_ALIGN_TOP,
							CRect(0, 0, 0, 0), IDR_TOLERANCE);
	mcsLoadToolbar(tb, IDR_TOLERANCE);
	CSize szToolBar = tb.CalcFixedLayout(FALSE, FALSE);
	tb.MoveWindow(&CRect(CPoint(0, 0), szToolBar), FALSE);
	int idRes = menu.Track(rcButton, &tb);
	if (idRes != IDCANCEL) {
		int iButton = tb.GetToolBarCtrl().CommandToIndex(idRes);
		// ...
	}
*/


/////////////////////////////////////////////////////////////////////////////
// CxComboBox window

class MECHCTL_API CxComboBox : public CComboBox
{
// Construction
public:
	CxComboBox();
	BOOL Create(const CRect &rc, CWnd* pParentWnd, UINT nID);
	int GetButtonWidth() { return GetSystemMetrics(SM_CXVSCROLL); }
	BOOL SelectItemByData(DWORD dwData);
protected:
	void DrawArrow(CDC *pDC,BOOL bPressed = FALSE);
	void DoDraw(CDC *pDC);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxComboBox)
	//}}AFX_VIRTUAL
	// Generated message map functions
protected:
	//{{AFX_MSG(CxComboBox)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrint(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL m_bButtonDown;
};

//---------------------------------------------------------------------------
__inline McsString MCS_LoadString(HINSTANCE ghInstance, UINT resourceID)
{
	return McsString((LPCTSTR)(UINT_PTR)(resourceID), ghInstance);
}

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// Color combobox
//---------------------------------------------------------------------------
#define NONE_COLOR 0xAA000000 // Отсутствие цвета, ничего не выбрано
class MECHCTL_API CMcColorComboBox : public CComboBox
{
public:

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int iItemHeight = -1);
	void Init(COLORREF color, DWORD dwFlags = 0, DWORD dwExtDropWidth = 0);
	COLORREF GetColor();
	void SelectColor(COLORREF color);

	CMcColorComboBox();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

		
	enum
	{
		kByLayer    = 0x01,
		kByBlock    = 0x02,
		kByLineType = 0x04,
		kByObject   = 0x08,

		kByLB       = 0x03,
		kByAll      = 0x0F,

		kByDefault  = 0x10,
		kSkipStdColors = 0x20,

		kByParamLinetype1 = 0x100,
		kByParamLinetype2 = 0x200,
	};

	// значения не менять!!! Сохраняются в чертеж! Зарезервированы для общего системного использования в McsGeometry.h
	enum
	{
		ENTCOLOR_BY_PARAM_LINETYPE9 = 0xF9000000,
		ENTCOLOR_BY_PARAM_LINETYPE8 = 0xF8000000,
		ENTCOLOR_BY_PARAM_LINETYPE7 = 0xF7000000,
		ENTCOLOR_BY_PARAM_LINETYPE6 = 0xF6000000,
		ENTCOLOR_BY_PARAM_LINETYPE5 = 0xF5000000,
		ENTCOLOR_BY_PARAM_LINETYPE4 = 0xF4000000,
		ENTCOLOR_BY_PARAM_LINETYPE3 = 0xF3000000,
		ENTCOLOR_BY_PARAM_LINETYPE2 = 0xF2000000,
		ENTCOLOR_BY_PARAM_LINETYPE1 = 0xF1000000
	};
private:
	DWORD m_dwFlags;
	COLORREF m_color;
	int m_iCustom, m_iItemHeight;
	McLogPix m_LP;
};

/////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// LineWeight combobox
//---------------------------------------------------------------------------
class MECHCTL_API CMcLineWeightComboBox : public CComboBox
{
public:

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, int iItemHeight = -1);
	void Init(int iLineWeight, DWORD dwFlags = 0, DWORD dwExtDropWidth = 0);
	int GetLineWeight();
	void SelectLW(int lw);

	CMcLineWeightComboBox();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	enum
	{
		kByLayer    = 0x01,
		kByBlock    = 0x02,
		kByLineType = 0x04,
		kByObject   = 0x08,
		kByDefault  = 0x10,

		kByLB       = 0x03,
		kByAll      = 0x1F,

		kByParamLinetype1 = 0x100,
		kByParamLinetype2 = 0x200,
	};

	// значения не менять!!! Сохраняются в чертеж! Зарезервированы для общего системного использования в McsGeometry.h
	enum
	{
		ENTWEIGHT_BY_PARAM_LINETYPE9 = -19,
		ENTWEIGHT_BY_PARAM_LINETYPE8 = -18,
		ENTWEIGHT_BY_PARAM_LINETYPE7 = -17,
		ENTWEIGHT_BY_PARAM_LINETYPE6 = -16,
		ENTWEIGHT_BY_PARAM_LINETYPE5 = -15,
		ENTWEIGHT_BY_PARAM_LINETYPE4 = -14,
		ENTWEIGHT_BY_PARAM_LINETYPE3 = -13,
		ENTWEIGHT_BY_PARAM_LINETYPE2 = -12,
		ENTWEIGHT_BY_PARAM_LINETYPE1 = -11
	};
private:
	DWORD m_dwFlags;
	int m_iItemHeight;
	int m_nLineLength;// длина черточки с толщиной линии
	mcsIntSet m_hsLineWeights;
	McLogPix m_LP;
};

//////////////////////////////////////////////////////////////////////////
// Edit с поддержкой размерности
class MECHCTL_API CxMenuHelper {
public:
	CxMenuHelper(DWORD aFlags = 0) : m_pStorage(NULL), m_dwFlags(aFlags) {};
	virtual ~CxMenuHelper()
	{
		if (m_pStorage)
			m_pStorage->Release();
	};
	//
	// Attributes
	// Ввод нижних индексов
	virtual BOOL IsSubscriptsAllowed();                            // default = TRUE
	virtual void AllowSubscripts(BOOL Value = TRUE);
	// Ввод верхних индексов
	virtual BOOL IsSuperscriptsAllowed();                          // default = TRUE
	virtual void AllowSuperscripts(BOOL Value = TRUE);
	// Ввод специальных символов
	virtual BOOL IsSymbolsAllowed();                               // default = TRUE
	virtual void AllowSymbols(BOOL Value = TRUE);
	// Разрешает вводить только действительные числа
	virtual BOOL IsNumeric();                                      // default = FALSE
	virtual void SetNumeric(BOOL bNumeric = TRUE);
	// Разрешает брать значения с чертежа
	virtual BOOL IsPickAllowed();
	virtual void AllowPick(BOOL Value = TRUE);                     // default = TRUE
	virtual BOOL IsHyperlinkAllowed();
	virtual void AllowHyperlink(BOOL Value);
	virtual BOOL IsPasteAllowed();
	virtual void AllowPaste(BOOL Value = TRUE);                    // default = TRUE
	// Разрешает RTF
	virtual BOOL IsRtfAllowed();                                   // default = FALSE
	virtual void AllowRtf(BOOL Value = TRUE);
	// Разрешает вставку материала. Включает в себя rtf с дробями.
	virtual BOOL IsMaterialAllowed();                              // default = FALSE
	virtual void AllowMaterial(BOOL Value = TRUE);
	//
	virtual HWND getHWND() = 0;
	IMcObject* m_pStorage;
	DWORD m_dwFlags;
};

class MECHCTL_API CxValueEdit : public CEdit, public CxMenuHelper
{
public:
	CxValueEdit();
	virtual ~CxValueEdit();
// 	BOOL Create(CWnd* pOwner, LPRECT pRect, int id, UINT uStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP);
	// Преобразовать содержимое поля в число и наоборот
	// (работает только если установлена категория, отличная от kmcUndefined). TODO!!
	bool GetValue(OUT double& rValue);
	bool SetValue(IN double rValue);
	McsString GetText();
	bool SetText(LPCTSTR lpszText);
	void SetIndefinite();
	// Косинцев С.Г., 20.02.2018:
	// Метод добавлен в рамках реализации диалога редактирования стиля мультивыноски. Проблема заключалась в том, что
	// при использовании редактора типа CxValueEdit в паре с UpDown контролом (когда редактор UpDown контролу задан
	// в качестве Buddy) затиралась нижняя кнопка UpDown контрола. Это происходило из-за непонятно зачем вызываемого
	// метода InvalidateRect() родителя редактора в методе CxValueEdit::OnEnUpdate(), который, по всей видимости,
	// затрагивал и UpDown контрол.
	// За неимением времени разобраться как следует и был добавлен метод SetWorksWithSpinCtrl(). Вызов этого метода со
	// значением true в качестве аргумента позволяет предотвратить вызов InvalidateRect() и UpDown контрол остаётся
	// в неприкосновенности.
	void SetWorksWithSpinCtrl(bool bState);

	HRESULT SetUnits(
		IN McUnits::MeasureCategory eCategory,
		IN OPTIONAL McUnits::Name eInputUnits = McUnits::kDefault,
		IN OPTIONAL McUnits::Name eDisplayUnits = McUnits::kDefault);
	bool ValidateValue(IN McsString aValue);
	MCSStringArray& GetValidationIgnoreArray() { return m_validationIgnoreList; };
	bool HasValidValue();

	// Подключить историю введенных значений
	bool SetHistory(LPCTSTR lpszKey = NULL, LPCTSTR lpszSubkey = NULL,
		int nHistoryCount = 10,       // к-во последних значений в списке (0 - не показывать список)
		int nRecentCount = 7);        // к-во шаблонных значений в списке (0 - не показывать список)
	// Добавить текущее содержимое поля в историю значений
	bool AddToHistory();
	// Всплывающая подсказка
	McsString GetTooltip();
	bool SetTooltip(McsString Value);
	COLORREF SetTextColor(COLORREF aNewColor);
	COLORREF SetBackColor(COLORREF aNewColor);
	COLORREF SetDimColor(COLORREF aNewColor);
	COLORREF SetErrorColor(COLORREF aNewColor);
	DECLARE_DYNCREATE(CxValueEdit)
	// CxMenuHepler
	virtual HWND getHWND() { return m_hWnd; };
	virtual BOOL IsSubscriptsAllowed() { return FALSE; };
	virtual BOOL IsSuperscriptsAllowed() { return FALSE; };
	virtual BOOL IsSymbolsAllowed() { return FALSE; };
	virtual BOOL IsPickAllowed() { return TRUE; };
	virtual BOOL IsHyperlinkAllowed() { return FALSE; };
	virtual BOOL IsPasteAllowed() { return true; };
	virtual BOOL IsMaterialAllowed() { return FALSE; }

	// Объект-хозяин для поддержки ссылок
	IMcObjectPtr m_pObject;

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) override;
	BOOL PreTranslateMessageInternal(MSG* pMsg);

	McUnits::MeasureCategory m_unitCategory; // значение McUnits::kmcUndefined отключает работу с именами размерностей
	McUnits::Name m_inputUnit;
	McUnits::Name m_displayUnit;
	McsString m_displayUnitMatchString;
	bool m_bIsDoubleDimension;

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnEnUpdate();
	afx_msg BOOL OnEnChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetWindowTextInternal(LPCTSTR pText);
	bool m_bSetWindowTextInternal;
	bool HasValidUnitString(LPCTSTR pStr);

	void PrepareBackground();
	DECLARE_MESSAGE_MAP()

	COLORREF m_TextColor;
	COLORREF m_ErrorColor;
	COLORREF m_DimColor;
	COLORREF m_BackColor;
	CBrush m_Brush;
	int m_nHistory;
	int m_nRecent;
	HWND m_hTooltip;
	McsString m_msTooltip;
	MCSStringArray m_validationIgnoreList; // shashkov: при больших размерах подумать об использовании map
	IMcUnitConverterPtr m_pUnitConverter;
	bool m_bIndefinite;
	bool m_bWorksWithSpinCtrl;
	friend class CxValueComboBox;
	double m_rValue;
	bool m_bValueChanged;
};

class MECHCTL_API CxValueComboBox : public CComboBox
{
public:
	CxValueComboBox();
	virtual ~CxValueComboBox();

	// ВНИМАНИЕ! Для работы с содержимым использовать только эти
	// методы. Не использовать методы из CComboBox.
	bool GetValue(OUT double& rValue); // Прочитать значение edit
	bool SetValue(IN double rValue); // Установить значение edit
	McsString GetText();
	bool SetText(LPCTSTR lpszText);
	BOOL IsNumeric();
	void SetIndefinite();
	
	bool AddValue(IN double rValue); // Добавить значение в listbox
	bool GetValue(IN int aIndex, OUT double& rValue); // Прочитать значение из listbox
	
	bool AddText(IN LPCTSTR lpszText); // Добавить текст в listbox
	McsString GetText(IN int aIndex); // Прочитать текст из listbox
	BOOL IsNumeric(IN int aIndex);
	

	HRESULT SetUnits(
		IN McUnits::MeasureCategory eCategory,
		IN OPTIONAL McUnits::Name eInputUnits = McUnits::kDefault,
		IN OPTIONAL McUnits::Name eDisplayUnits = McUnits::kDefault);
	bool ValidateValue(IN McsString aValue);
	MCSStringArray& GetValidationIgnoreArray() { return m_edit.GetValidationIgnoreArray(); };

	// Подключить историю введенных значений
	bool SetHistory(LPCTSTR lpszKey = NULL, LPCTSTR lpszSubkey = NULL,
		int nHistoryCount = 10,       // к-во последних значений в списке (0 - не показывать список)
		int nRecentCount = 7);        // к-во шаблонных значений в списке (0 - не показывать список)
	// Добавить текущее содержимое поля в историю значений
	bool AddToHistory();

	BOOL SubclassDlgItem(UINT nID, CWnd* pParent);
	// windowsx.h определяет макрос SubclassWindow, он подставляется сюда, и нихрена не собирается.
#ifdef SubclassWindow
#undef SubclassWindow
#endif
	BOOL SubclassWindow(HWND hwnd);
	DECLARE_DYNCREATE(CxValueComboBox)
protected:
	McUnits::MeasureCategory m_unitCategory; // значение McUnits::kmcUndefined отключает работу с именами размерностей
	McUnits::Name m_inputUnit;
	McUnits::Name m_displayUnit;
	McsString m_displayUnitMatchString; //*
	bool m_bIsDoubleDimension;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditChange();

	// Хранлище для обёртки edit
	CxValueEdit m_edit;
	bool m_bHasEditControl;
	MCSDoubleArray m_values; // holder для хранения копий значений из listbox
	MCSIntArray m_types; // тип значения: 0 - текст, 1 - double
	IMcUnitConverterPtr m_pUnitConverter;
};

//---------------------------------------------------------------------------
class CMcClipboard
{
	bool m_isOpen;
public:
	CMcClipboard(HWND hWnd)
	{
		m_isOpen = !!OpenClipboard(hWnd);
	}
	~CMcClipboard()
	{
		if(m_isOpen)
			CloseClipboard();
	}
	bool isOpen()
	{
		return m_isOpen;
	}
};

//////////////////////////////////////////////////////////////////////////
// Edit с поддержкой индексов
class MECHCTL_API CxFtEdit : public CRichEditCtrl, public CxMenuHelper
{
public:
	BOOL Create(CWnd* pOwner, LPRECT pRect, int id,
							UINT uStyle = WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_AUTOHSCROLL
							// for multiline use WS_VSCROLL|WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_MULTILINE|ES_WANTRETURN
							);

	// Подсветка ключевых слов
	struct KW_Color {
		McsString msKeyword;
		COLORREF clFont;
		bool fMatchCase;
		//COLORREF clBackground;
		KW_Color() : clFont(0), fMatchCase(true) {}
		KW_Color(LPCTSTR strKeyword, COLORREF cl, bool fCase = true) : msKeyword(strKeyword), clFont(cl), fMatchCase(fCase) {}
	};
	McsArray<KW_Color, const KW_Color&> m_Keywords;
	// Всплывающая подсказка
	McsString GetTooltip();
	void SetTooltip(McsString Value);
	// Внешние ссылки
	//   p         - объект, свойство которого редактируется. В нем будут храниться ссылки.
	//   iGsMarker - графический маркер текста, привязанного к этому свойству.
	//   stProperty - название текстового свойства объекта, соответствующего даанному полю.
	//   dwFlags   - флажки CXFT_*
#define CXFT_SELECT_SHEET        0x00000001  // добавлять в контекстное меню выбор листа
	void SetObject(IMcObject* p, int iGsMarker, DWORD dwFlags = 0);
	void SetObject(IMcObject* p, LPCTSTR stProperty, DWORD dwFlags = 0);

	// Задаёт шрифт по умлочанию всему содержимому контрола.
	void MakeFontDefault();
	void SetFontSize(int iFontSize);

// Field access
	// Текст в rtf-формате
	McsString GetText();
	BOOL SetText(LPCTSTR lpszText);
	// У CRichEditCtrl::GetSelText нет уникодной версии.
	CString GetSelText() { MCSASSERTE(_T("Use GetSelText2 function")); return _T(""); }
	McsString GetSelText2();
	BOOL InsertSymbol(WCHAR Value);
	// Преобразовать содержимое поля в число и наоборот (работает только если IsNumeric() != FALSE)
	BOOL GetValue(double& rValue);
	void SetValue(double rValue);

	// Получает размер текста для индексов и дробей.
	IMcTextConverter::FractionTextSize GetFractionTextSize();
	// Задаёт размер текста для индексов и дробей.
	void SetFractionTextSize(IMcTextConverter::FractionTextSize fts);

	// Получает значение, указывающее, будет ли редактор рисовать дополнительную графику, не поддерживаемую RichEdit.
	bool UseOverlayPaint();
	// Задаёт значение, указывающее, будет ли редактор рисовать дополнительную графику, не поддерживаемую RichEdit.
	void SetUseOverlayPaint(bool bUseOverayPaint);

// Functions
	// Получить интерфейс IMcTextConverter, проинициализированный этим контролом.
	// Все операции над интерфейсом будут отражться на содержимом контрола.
	// Флажки IsSubscriptsAllowed, IsSuperscriptsAllowed, IsSymbolsAllowed, IsNumeric игнорируются
	IMcTextConverterPtr GetTextConverter();

	// Подключить историю введенных значений
	BOOL SetHistory(LPCTSTR lpszKey = NULL, LPCTSTR lpszSubkey = NULL,
		int nHistoryCount = 10,       // к-во последних значений в списке (0 - не показывать список)
		int nRecentCount = 7);        // к-во шаблонных значений в списке (0 - не показывать список)
	// Добавить текущее содержимое поля в историю значений
	BOOL AddToHistory();

	BOOL SubclassDlgItem(UINT nID, CWnd* pParent);
// windowsx.h определяет макрос SubclassWindow, он подставляется сюда, и нихрена не собирается.
#ifdef SubclassWindow
#undef SubclassWindow
#endif
	BOOL SubclassWindow(HWND hwnd);

// Messages
	// Вызывается после создания контекстного меню перед TrackPopupMenu
	// В обработчике можно добавить свои пункты после пункта lParam
	// ID пунктов > 40500
	#define WM_FTEDIT_ONPOPUP         (WM_USER+0x7f1)
	// wParam = HMENU
	// lParam = custom menu item index to insert at
	
public:
	CxFtEdit();
	virtual ~CxFtEdit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL _PreTranslateMessage(MSG* pMsg);
	
	// Объект-хозяин для поддержки ссылок
	CDbEntityPrototypePtr m_pEntity;
	// Текстовое свойство хозяина, связанного с этим контролом
	McsString m_stProperty;

	bool m_bFractionSizeSet;

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void ValidateValue(McsString ms);
	HRESULT ClipboardCopy(UINT message);
	HRESULT ClipboardPaste();

public:
	// CxMenuHepler
	virtual HWND getHWND() { return m_hWnd; };

protected:
	DWORD m_dwObject;
	int m_nHistory;
	int m_nRecent;
	HWND m_hTooltip;
	McsString m_msTooltip;
	CFont m_Font;
	IMcTextConverter::FractionTextSize m_fractionTextSize;
	bool m_bUseOverlayPaint;

#pragma region http://www.codeguru.com/cpp/controls/richedit/conversions/print.php/c8729
	void VerifyThemedBorderState();
	bool NCPaint();
	bool NCCalcSize(NCCALCSIZE_PARAMS *csparam);
#pragma endregion
	void OverlayPaint(FORMATRANGE *lpFormatRange);
};

//////////////////////////////////////////////////////////////////////////
// Класс, производящий конвертацию записей записной книжки нового формата в старый
class MECHCTL_API NotebookRecordConverter
{

public:
	NotebookRecordConverter();
	~NotebookRecordConverter();

	McsString ConvertNotebookRecordContent(const McsString& sContent, int iRetType);


};

#define	WM_CS_RECALCLAYOUT		(WM_USER + 101)
/////////////////////////////////////////////////////////////////////////////
// CxSplitter window
class MECHCTL_API CxSplitter : public CWnd {
	
public:
	// Construction
	CxSplitter();
	// Destruction
	virtual ~CxSplitter();
	
public:
	// Bind splitter window with control
	void BindWithControl(CWnd* pParentWnd, DWORD dwID, BOOL bHoriz = TRUE);
	// Unbind splitter
	void Unbind();
	
	// Attach panes
	void AttachAsLeftPane(DWORD dwID, WORD offset=0, WORD isControl = 0);
	void AttachAsRightPane(DWORD dwID, WORD offset=0, WORD isControl = 0);
	// Detach panes
	void DetachAllPanes();
	
	// Set min width panes
	void SetMinWidth(int iMinLeft, int iMinRight);
	
	// Recalc layout
	void RecalcLayout();
	
protected:
	// Get mouse cliping rectangle
	BOOL getMouseClipRect(LPRECT rectClip, CPoint point);
	
protected:
	//{{AFX_MSG(CxSplitter)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
protected:
	// Pointer on parent class CWnd
	CWnd* m_pParentWnd;
	
	// Left and right pane
	CDWordArray m_LeftPane;
	CDWordArray m_RightPane;
	CWordArray m_RightPaneOffset;
	CWordArray m_RightPaneIsControl;
	CWordArray m_LeftPaneOffset;
	CWordArray m_LeftPaneIsControl;
	// Minimal left and right width pane
	int m_iMinLeft;
	int m_iMinRight;
	BOOL m_bHoriz;
	// 19.03.2009, AGL
	bool m_fBound;
};

/////////////////////////////////////////////////////////////////////////////
// CxMaskedEdit - CEdit for entering real/int numbers by mask
class MECHCTL_API CxMaskedEdit: public CEdit
{
protected:
	int m_point;
	int m_len;

public:
	// for mask "123.45678" point is 4, len is 9
	//if point is negative -> no point
	CxMaskedEdit(int point, int len);
	virtual void ReInit(int point, int len);

	virtual ~CxMaskedEdit();

	virtual int GetPointPos() const; //negative if point is absent (as set in Init)
	virtual int GetMaskLength() const; //return full field length (as set in Init)

	virtual McsString GetString() const;	//get string as is
	virtual int GetIntNumber() const;		//double value truncated by static type conversion
	virtual double GetRealNumber() const;	//double value

	//numbers are fit into selected mask
	virtual void SetNumber(int number);
	virtual void SetNumber(double number);

protected:
	virtual void correctMask();
	virtual void zeroRange(int iStart, int iEnd);
	virtual void SetCharAt(UINT nChar, int pos);

protected:
	virtual void OnChar(UINT nChar,	UINT nRepCnt, UINT nFlags);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// Сообщения CxPropertyPage
#define PPM_SETFOCUS     (WM_USER+0x01f9)  // Начало редактирования примитива
// wParam - McsEntityGeometry* редактируемый примитив
// lParam - HRESULT* установить в E_FAIL, чтобы запретить редактирование
// еще бы точку сюда передать...

#define PPM_KILLFOCUS    (WM_USER+0x01fa)  // Конец редактированя примитива
// wParam - McsEntityGeometry* новое значение. Можно изменять.
// lParam - HRESULT* установить в E_FAIL, чтобы отменить изменение

#define PPM_HISTORY      (WM_USER+0x01fb)  // Запрос списка последних значений для текста
// wParam - McsEntityGeometry* примитив (mcsText)
// lParam - McsString* имя списка последних значений для IMcRecentValues

#define PPM_FIELD_SIZE (WM_USER+0x01fc)  // Вычисление размера поля
// wParam - McsEntityGeometry*
// lParam - CRect* размер поля ввода

McsString MECHCTL_API MCS_OpenFolder(LPCTSTR strDefaultFolder = NULL, HWND hwnd = NULL);

//////////////////////////////////////////////////////////////////////////
// Popup-диалог выбора стрелки
HRESULT MECHCTL_API SelectArrowDlg(IN OUT MCS_ARROW* pArrow,
																	 IN POINT* ppt,
																	 IN const MCS_ARROW* pAllowedArrows = NULL,
																	 IN int nAllowedArrows = 0,
																	 IN HWND hParent = NULL);

//------------------------------------------------------------------------
HRESULT MECHCTL_API DeviationsOf(
	IN LPCTSTR pszField,
	IN double rSize,
	OUT double& rES,
	OUT double& rEI);

//------------------------------------------------------------------------
// Диалог выбора допусков из таблицы
HRESULT MECHCTL_API SelectFitsDlg(
	IN OUT IMcDimension* pDim,
	IN OPTIONAL HWND hParent = NULL,
	IN OPTIONAL bool fDisableAssemble = false);

// ------------------------------------------------------------------------
// Диалог выбора допусков из таблицы
HRESULT MECHCTL_API SelectFitsDlgWithoutParent(IN OUT IMcDimension* pDim);

//------------------------------------------------------------------------
// Диалог свойств штриховки
enum McHatchFieldEnum
{
	hf_Invisible      = 0x00000001,
	hf_Color          = 0x00000002,
	hf_LineType       = 0x00000004,
	hf_LineWeight     = 0x00000008,
	hf_PatternType    = 0x00000010,
	hf_PatternName    = 0x00000020,
	hf_PatternScale   = 0x00000040,
	hf_PatternAngle   = 0x00000080,
	hf_PatternSpacing = 0x00000100,
	hf_PatternDouble  = 0x00000200,
	hf_PatternBgColor = 0x00000400,
	hf_PatternOrigin  = 0x00000800,
};
// Маски dwUndefinedFieldsMask и dwHiddenFieldsMask формируются из флагов McHatchFieldEnum
HRESULT MECHCTL_API ShowHatchDialog(IN OUT McsEntityGeometry& geomAsHatch, IN HWND hParent = NULL, DWORD dwUndefinedFieldsMask = 0, DWORD dwHiddenFieldsMask = 0);
HRESULT MECHCTL_API GetHatchXmlParams(IN const McsEntityGeometry& geomAsHatch, OUT mcsStringArrayW& arrHPNames, OUT mcsStringArrayW& arrHPValues);
HRESULT MECHCTL_API InitHatchByXmlParams(IN const mcsStringArrayW& arrHPNames, IN const mcsStringArrayW& arrHPValues, OUT McsEntityGeometry& geomAsHatch);

//////////////////////////////////////////////////////////////////////////
#define DTSF_STYLE              0x00000001    // Стиль текста
#define DTSF_COLOR              0x00000002    // Цвет текста
#define DTSF_HEIGHT             0x00000004    // Высота текста
#define DTSF_TEXT               0x00000008    // Строка
#define DTSF_XSCALE             0x00000010    // Коэффициент сжатия
#define DTSF_OBLIQUE            0x00000020    // Угол наклона
#define DTSF_NO_SUBSUPER        0x00000040    // Запретить индексы
#define DTSF_NO_SYMBOLS         0x00000080    // Запретить спецсимволы
#define DTSF_NO_HYPERLINK       0x00000100    // Запретить гиперссылку
#define DTSF_LINE_SPACING       0x00000200    // Межстрочный интервал
#define DTSF_ALL_OPTIONS        (0x0000FFFF&(~(DTSF_NO_SUBSUPER|DTSF_NO_SYMBOLS)))

#define DTSF_CLR_LAYER          0x00010000    // Разрешить цвет по слою
#define DTSF_CLR_BLOCK          0x00020000    // Разрешить цвет по блоку
#define DTSF_CLR_LINETYPE       0x00040000    // Разрешить цвет по типу линии
#define DTSF_CLR_OBJECT         0x00080000    // Разрешить цвет по объекту
#define DTSF_ALLCLR_SYSTEM      (DTSF_CLR_LAYER|DTSF_CLR_BLOCK)
#define DTSF_ALLCLR             0xFFFF0000

//////////////////////////////////////////////////////////////////////////
// Редактирование свойств текста из диалога
extern "C"
HRESULT
MECHCTL_API
EditText(IN HWND hParent,                           // окно, откуда вызывается диалог
         IN OUT McsEntityGeometry& Text,            // mcsText с нужными настройками
         IN OPTIONAL DWORD dwFlags = DTSF_ALL_OPTIONS|DTSF_ALLCLR_SYSTEM,
         IN OPTIONAL LPCTSTR lpszModule = NULL,     // Имя библиотеки для истории ввода
         IN OPTIONAL LPCTSTR lpszName = NULL,       // Имя параметра для истории ввода
         IN OPTIONAL IMcObject* pOwner = NULL);     // Объект-хозяин текста

//---------------------------------------------------------------------------
struct McEditNativeTextData
{
	mcsWorkID id;
	mcsText text;
	mcsPoint pnt1;
	mcsPoint pnt2;
	mcsVector normal;
	mcsVector direction;
	double rScale;
	double rMTextHeight;
	double rMTextWidth;
	COLORREF nColor;
	bool isAlignValid;
	bool isTextStringValid;
	bool isTextFit;
	bool isTextAligned;
	bool isDiffHeight;
	bool isDiffOblique;
	bool isDiffXScale;
	McEditNativeTextData()
	{
		rScale = 1;
		rMTextHeight = 0;
		nColor = 0;
		isAlignValid = true;
		isTextStringValid = true;
		isTextFit = false;
		isTextAligned = false;
		isDiffHeight = false;
		isDiffOblique = false;
		isDiffXScale = false;
	}
};
typedef void (*McEditNativeTextProc)(McEditNativeTextData& data);
extern "C" MECHCTL_API HRESULT McEditNativeText(const McEditNativeTextData& data, McEditNativeTextProc pCallback);

//////////////////////////////////////////////////////////////////////////
// Магнитный выбор траектории (как Magnet lasso в Photoshop)
HRESULT
MECHCTL_API
MagnetSelectTrajectory(OUT mcsPolyline& Trajectory,              // результат выбора
                       IN OPTIONAL bool fTangential = false);    // выбор по касательным (для ременных и цепных передач)

// То же самое, но позволяет передать начальную траекторию, которая будет продолжаться магнитом.
HRESULT
MECHCTL_API
MagnetSelectTrajectoryEx(IN const mcsWorkID& idLastSnapped,      // ID объекта, с которого взяли последнюю точку Trajectory
                         IN OUT mcsPolyline& Trajectory,         // результат выбора. Он же - исходный контур
                         IN OPTIONAL bool fTangential = false);  // выбор по касательным (для ременных и цепных передач)


//////////////////////////////////////////////////////////////////////////
// Создание кнопки "взять с чертежа" рядом с полем ввода
HWND MECHCTL_API CreateMeasureButton(HWND hControl,
																		 MeasureShema Default = kMcMeasureDistance,
																		 DWORD dwAllowed = -1);
// После удачного завершения измерений родителю поля ввода придет сообщение WM_NOTIFY с такой структурой:
#define NM_MEASURED  (0U-1073U)
struct NMMEASURE : public NMHDR {
	//HWND	hwndFrom;     = поле ввода
	//UINT	idFrom;       = ID поля ввода
	//UINT	code;         = NM_MEASURED
	HWND hButton;      // = кнопка
	MeasureInfo* pmi;  // = данные о режиме измерения
};


//////////////////////////////////////////////////////////////////////////
// fLock = FALSE - скрывает окно hActive и всех его предков до основного окна приложения,
//                 разблокирует основное окно приложения.
// fLock = TRUE восстанавливает всю цепочку окон и возвращает модальность окну hActive
//
// ВАЖНО: Каждый вызов LockMainWnd( , FALSE) всегда должен сопровождаться парным ему LockMainWnd(, TRUE)
// Для большей безопасности рекомендую использовать класс MainWndLocker
HRESULT MECHCTL_API LockMainWnd(HWND hActive, BOOL fLock);


//////////////////////////////////////////////////////////////////////////
// Автоматически разблокирует основное окно приложения при создании экземпляра класса
// и возвращает всё на место после уничножения
struct MainWndLocker {
	HRESULT m_hr;
	HWND m_hActive;
	MainWndLocker(HWND hActive) : m_hActive(hActive) { m_hr = LockMainWnd(hActive, FALSE); }
	~MainWndLocker() { if (S_OK == m_hr) LockMainWnd(m_hActive, TRUE); }
};

//////////////////////////////////////////////////////////////////////////
//Установливает стиль "explorer" на контролы, например в дереве вместо плюсиков - треуголнички, более внятная неактивная селекция и прочее
//вобщем если что то хочется как в эксполрере...
typedef HRESULT (__stdcall *SetWindowThemeFunc)(HWND hwnd, LPCWSTR pszSubAppName,	LPCWSTR pszSubIdList);
__inline bool SetExtendedThemeStyle(HWND hWnd){
	if(1 == mcsGetIntOption(_T("BlockExplorerTheme"), 0, _T("MechCtl"))){
		return false;
	}
	SetWindowThemeFunc pFunc;
	DYN_GET_PROC_ADDRESS(pFunc, _T("UxTheme.dll"), "SetWindowTheme",NULL);
	if(pFunc){
		pFunc(hWnd, L"explorer", NULL);
		return true;
	}
	return false;
}

// #6844
/*
//////////////////////////////////////////////////////////////////////////
// Show object tooltip
BOOL MECHCTL_API
MCS_TrackToolTip(IN POINT ptScreen,                                    // screen coordinates of top left tooltip's cornet
								 IN LPCTSTR strText,                                   // tooltip text. supports tables, line breaks, special symbols
								 IN OPTIONAL const mcsWorkID& idObject = GUID_NULL,    // null idObject hides tooltip
								 IN OPTIONAL BOOL fEditable = TRUE);                   // add "Edit" link to tooltip text
*/

#define WM_END_MOVING_SPLITTER	WM_USER+306

#include "Controls/CxTreeListCtrl.h"
#include "Controls/TreeCtrlEx.h"
#include "Controls/CxImage.h"

/*#ifndef MFC7
typedef unsigned long ULONG_PTR, *PULONG_PTR;
#include "..\Extern\GDI+\inc\gdiplus.h"
#pragma comment(lib, "GdiPlus.lib")
#endif //MFC7
*/
#endif // MECHCTL_NO_FMC



//////////////////////////////////////////////////////////////////////////
// Добавляет к hStatic рамку в соответствии с темой оформления Windows.
// Можно применять для любых контролов, у которых рамка выглядит неправильно,
// но учтите, что состояние контрола (disabled, focused, hot, ...)
// на рамке отражаться не будет.
// Рамка переопределяется, только если у контрола есть стиль WS_BORDER и/или
// расширенный стиль WS_EX_CLIENTEDGE.
bool MECHCTL_API MakeStaticThemed(HWND hStatic);


//////////////////////////////////////////////////////////////////////////
// Вычисляет координаты всплывающего окошка.
// Аналог CalculatePopupWindowPosition, которая появилась только в Win7 и Server2008
// http://msdn.microsoft.com/en-us/library/dd565861(v=vs.85).aspx
BOOL MECHCTL_API _CalculatePopupWindowPosition
(
  __in      const POINT *anchorPoint,
  __in      const SIZE  *windowSize,
  __in            UINT  flags,
  __in_opt        RECT  *excludeRect,
  __out           RECT  *popupWindowPosition
);


McsString MECHCTL_API getWindowText(HWND hWnd);


//////////////////////////////////////////////////////////////////////////
// Выбирает из строки msList числовые индексы.
// Варианты записи:
// "1,2,3"
// "1-4,5,7-10"
// "-5"             // с iMin по 5
// "5-"             // с 5 по iMax
// "-3,10-15,20-"   // можно так: "/3;10/15;20/"
HRESULT MECHCTL_API ParseIndexList(IN McsString msList, IN int iMin, IN int iMax, OUT mcsIntArray& iiSelected);


//////////////////////////////////////////////////////////////////////////
interface IMcGesture : public IMcObject
// Обеспечивает управление жестами мыши.
// Жест - перетаскивание мыши по определённой траектории с нажатой правой кнопкой.
// Траектория движения отрисовывается в окне, пока нажата правая кнопка. В процессе
// ввода рядом с курсором показывается имя и иконка команды, соответствующей этому
// жесту.
//
//
// Пример использования
//
// class CMyWnd : public CDialog {
// public:
//   IMcGesturePtr m_pGesture;
//   BOOL OnInitDialog() {
//     m_pGesture = gpMcObjManager->createObject(IID_IMcGesture);
//     m_pGesture->Register(_T("Edit.Undo"), ID_EDIT_UNDO, ID_IMG_UNDO, LS(IDS_EDIT_UNDO));
//     m_pGesture->Register(_T("Edit.Redo"), ID_EDIT_REDO, ID_IMG_REDO, LS(IDS_EDIT_REDO));
//     m_pGesture->Register(_T("Edit.Cut"), ID_EDIT_CUT, -1, LS(IDS_EDIT_CUT));
//     m_pGesture->Register(_T("Help"), IDHELP, -1);
//     m_pGesture->Add(_T("UR"), ID_EDIT_UNDO);
//     m_pGesture->Add(_T("UL"), ID_EDIT_REDO);
//     m_pGesture->Add(_T("URDLD"), IDHELP, ID_IMG_HELP);
//     m_pGesture->SetName(_T("MyWnd"));
//     m_pGesture->AttachTo(GetDlgItem(IDC_EDIT_TEXT)->GetSafeHwnd(), m_hWnd);
//     // ...
//     return TRUE;
//   }
// };
{
public:
	// Подключает управление жестами к окну hParent. hOwner - окно, которому будут приходить
	// команды (если NULL, команды присылаются окну hParent)
	virtual HRESULT AttachTo(IN OPTIONAL HWND hParent = NULL, IN OPTIONAL HWND hOwner = NULL) = 0;

	// Добавляет жест и связывает с ним команду.
	// Жест задаётся в strGesture последовательностью букв U (вверх), D (вниз), R (вправо) и L (влево)
	// Длина штрихов не нормируется, последовательности из одинаковых букв использовать нельзя.
	// Если iImage и strLocalized уже определены в Register, здесь их можно не указывать
	virtual HRESULT Add(IN LPCTSTR strGesture, IN UINT idCommand, IN OPTIONAL int iImage = -1, IN OPTIONAL LPCTSTR strLocalized = NULL) = 0;

	// Регистрирует команду, для которой можно задать жест. Если все жесты заданы в коде, через Add,
	// то эту функцию можно не вызывать. strLocalized используется в качестве подсказки при вводе
	// жеста. Если не указана, подсказка формируется автоматически, из главного меню диалога.
	virtual HRESULT Register(IN LPCTSTR strName, IN UINT idCommand, IN OPTIONAL int iImage = -1, IN OPTIONAL LPCTSTR strLocalized = NULL) = 0;

	// Имя раздела в хранилище, куда сохраняется набор жестов. Если в хранилище что-то есть,
	// все жесты, добавленные в Add, будут удалены, а вместо них зачитаются жесты из хранилища.
	virtual HRESULT SetName(IN LPCTSTR strName) = 0;

	// Удалить все жесты, добавленные в Add. На зарегистрированные команды не влияет.
	virtual HRESULT Clear() = 0;

	// Редактировать список жестов. Работает только если присоединено хранилище (SetName)
	virtual HRESULT Edit() = 0;

	// Выдаёт подробную информацию о последнем жесте: точку начала и конца жеста, габариты
	// нарисованной кривой (всё в координатах hParent). Возвращает буквенный код жеста.
	virtual McsString GetExtraInfo(OUT OPTIONAL LPPOINT pptStart = NULL, OUT OPTIONAL LPPOINT pptEnd = NULL, OUT OPTIONAL LPRECT prcBounds = NULL) = 0;
};

// Сообщение присылается окну hOwner в процессе ввода жеста, если такой жест не зарегистрирован
#define WM_GESTURE_CALLBACK	WM_USER+307
// wParam - LPUINT - сода можно положить идентификатор команды
// lParam - LPCTSTR - описание жеста

// Сообщение присылается окну hOwner по окончании ввода незарегистрированного жеста
#define WM_GESTURE_UNKNOWN	WM_USER+308
// lParam - LPCTSTR - описание жеста

// Стандартные жесты для Add
#define MCS_GESTURE_UNDO               _T("UL")            // отменить
#define MCS_GESTURE_REDO               _T("UR")            // вернуть
#define MCS_GESTURE_BACKWARD           _T("L")             // назад
#define MCS_GESTURE_FORWARD            _T("R")             // вперёд
#define MCS_GESTURE_HELP               _T("URDLD")         // справка (нарисовать "?")
#define MCS_GESTURE_CLEAR1             _T("LRL")           // очистить, удалить
#define MCS_GESTURE_CLEAR2             _T("RLR")           // то же самое, чтобы не запоминать, в какую сторону зачёркивать


McsString MECHCTL_API FormatColorValue(COLORREF color);



//=============================================================================

#if !defined(_NCAD_BUILD_) && !defined(_MCS_CORE_ONLY)
	#include "MechCtlInternal.h"
#endif

//=============================================================================


// вспомогательная функция для запуска диалога просмотра блоков документа (определяется именем файла) предустановленный блок и выбранный, определяются параметром blockName
HRESULT MECHCTL_API _LaunchDialogPreviewBlocksOfDocument(IN OUT McsString& fileName, IN OUT McsString& blockName, OUT mcsWorkID& idBlock, HWND m_hWnd);


// Функция добавлена в рамках требования добавить возможность размещения таблицы
// допусков на чертеже из диалога "Групповое редактирование размеров" (команда
// "dimeditgroup"). Реализация функции находится в McDimWizzard.cpp.
void MECHCTL_API PlaceFitList(void);

//---------------------------------------------------------------------------
bool MECHCTL_API McCanFrameworkTakeFocus(HWND hContainer);


//===========================================================================================================================================
// Общие функции для работы с шаблонами из Базы элементов. Объявлены в MechCtl, т.к. используются и в Net-модулях (McArchitecture через Mapimngd), и в нативных (PTDialogs).

//---------------------------------------------------------------------------------------------------------------------------------------
// Сохраняет pEntity в Базе Элементов предварительно показав пользователю диалог сохранения.
// Имя шаблона в диалоге берется из sTemplateName. Если не указано, то берется последнее использованное имя.
// Параметры сохранения настраиваются предварительным вызовом функции RegisterEntityObjectContainer для соответствующего класса McEntity.
// Если такой регистрации произведено не было, то будут использованы параметры для стен (если они были зарегистрированы) - такое поведение было раньше.
extern "C" HRESULT MECHCTL_API McSaveObjectAsTemplate(IMcEntity* pEntity, const McsString& sTemplateName, MCSUID* pUid = NULL);

//---------------------------------------------------------------------------------------------------------------------------------------
// Регистрирует для указанного класса объекта:
// - соответствующий ему класс контейнера Базы Элементов;
// - используемый по-умолчанию путь в Базе элементов;
// - префикс для ключей реестра, используемых функцией McSaveObjectAsTemplate для сохранения параметров между вызовами.
extern "C" void MECHCTL_API RegisterEntityObjectContainer(const GUID& entityClassID, const GUID& objectContainerClassID, const McsString& sDefaultDbPath, const McsString& sRegPrefix);

//---------------------------------------------------------------------------------------------------------------------------------------
// Запись внешнего файла в документ as CustomData.
// - пишется в dictionary по уникальному имени
HRESULT MECHCTL_API WriteDataToDocFromExternalFile(IMcDocument* pDoc, LPCTSTR pszFilePathName, LPCTSTR pszCustomName);
// Чтение CustomData и запись во внешний файл.
HRESULT MECHCTL_API ReadDataFromDocToExternalFile(IMcDocument* pDoc, LPCTSTR pszFilePathName, LPCTSTR pszCustomName);
//---------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------------------------
// Конвертация RawMText <--> McMTextSimpleChunkArray
//---------------------------------------------------------------------------------------------------------------------------------------
struct McMTextFractionData
{
// Формат дробей в MText:
// В АКАД 4 типа дробей. Отличаются способом отображения на чертеже и используемыми символами разделения числителя от знаменателя в rawtext.
// 1. Первый тип    - "Горизонтальная дробь". Делитель - '/'. На чертеже делитель - горизонтальная линия.
// 2. Второй тип    - "Диагональная дробь".   Делитель - '#'. На чертеже делитель - диагональная линия. (прямой слэш)
// 3. Третий тип    - "Допуск".               Делитель - '^'. На чертеже делитель не отображается.
// 4. Четвертый тип - "Десятичная".           Делитель - '~'. На чертеже делитель не отображается. После делителя в rawtext следует символ десятичного разделителя!
// 
// Третий тип дробей используется в MText для отображения верхнего и нижнего индекса!
// Четвертый тип дробей умеет выравнивать числитель и знаменатель относительно десятичного разделителя.

	McsString m_sTopText;    // Числитель
	McsString m_sBottomText; // Знаменатель
	TCHAR m_cDivider;        // Делитель
	TCHAR m_cDecSeparator;   // Десятичный разделитель

	McMTextFractionData() :
		m_cDivider('\0'),
		m_cDecSeparator('\0')
	{
	}
};

struct McMTextSimpleChunk
{
	enum ChangeFlags
	{
		kLineSpacing  = 0x01,
		kTextSize     = 0x02,
		kIndexColor   = 0x04,
		kColor        = 0x08,
		kXScale       = 0x10,
		kObliqueAngle = 0x20,
	};

	McsString m_sText;    // текст, заполняется если не дробь, не табулятор, не конец строки/новый параграф

	// Флаги
	bool m_bBold;           // жирный
	bool m_bItalic;         // курсив
	bool m_bUnderlined;     // подчёркнутый
	bool m_bOverlined;      // надчеркнутый
	bool m_bStriked;        // зачеркнутй
	bool m_bTab;            // табулятор
	bool m_bLineBreak;      // конец строки
	bool m_bNewParagraph;   // новый параграф
	bool m_bNewLineSpacing; // межстрочный интервал

	double m_rLineSpacing;  // Значение межстрочного интервала
	double m_rTextSize;     // коэффициент изменения высоты шрифта относительно высоты текстового стиля
	int m_indexColor;       // индекс цвета 1-red,2-yellow,3-green,4-cyan,5-blue,6-magenta,7-black/white
	COLORREF m_Color;       // цвет RGB
	double m_rXScale;       // коэффициент сжатия текста
	double m_rObliqueAngle; // угол наклона

	// Опциональные параметры дроби
	bool m_bFraction;
	McMTextFractionData m_dataFraction;

	// Флаги изменения числовых параметров
	DWORD m__dwChangeFlags;
	bool IsLineSpacingChanged()  const { return !!(m__dwChangeFlags & McMTextSimpleChunk::kLineSpacing); }
	bool IsTextSizeChanged()     const { return !!(m__dwChangeFlags & McMTextSimpleChunk::kTextSize); }
	bool IsIndexColorChanged()   const { return !!(m__dwChangeFlags & McMTextSimpleChunk::kIndexColor); }
	bool IsColorChanged()        const { return !!(m__dwChangeFlags & McMTextSimpleChunk::kColor); }
	bool IsXScaleChanged()       const { return !!(m__dwChangeFlags & McMTextSimpleChunk::kXScale); }
	bool IsObliqueAngleChanged() const { return !!(m__dwChangeFlags & McMTextSimpleChunk::kObliqueAngle); }

	McMTextSimpleChunk() :
		m__dwChangeFlags(0),
		m_bBold(false),
		m_bItalic(false),
		m_bUnderlined(false),
		m_bOverlined(false),
		m_bStriked(false),
		m_bTab(false),
		m_bLineBreak(false),
		m_bNewParagraph(false),
		m_bNewLineSpacing(false),
		m_rLineSpacing(1.0),
		m_rTextSize(0.0),
		m_indexColor(0),
		m_Color(0),
		m_bFraction(false),
		m_rXScale(1.0),
		m_rObliqueAngle(0.0)
	{
	}
};
typedef McsArray<McMTextSimpleChunk, const McMTextSimpleChunk&> McMTextSimpleChunkArray;

extern "C" bool MECHCTL_API ConvertRawMTextToSimpleChunks(IN LPCTSTR pszRawMTextContent, OUT McMTextSimpleChunkArray& chunks, IN OPTIONAL LPCTSTR pszTextStyleName = NULL);
extern "C" bool MECHCTL_API ConvertSimpleChunksToRawMText(IN const McMTextSimpleChunkArray& chunks, OUT McsString& sRawMTextContent);
//---------------------------------------------------------------------------------------------------------------------------------------

/// <summary>
/// Создаёт пустой контейнер для пользовательского содержимого.
/// </summary>
/// <returns>Указатель на интерфейс IMcWindowContainer, если создание контейнера прошло успешно, или NULL.</returns>
MECHCTL_API IMcWindowContainer* CreateDefaultIMcWindowContainer();

/// <summary>
/// Создаёт контейнер, заполненный указанным пользовательским содержимым.
/// </summary>
/// <param name="pContentWindow">Окно с пользовательским содержимым.</param>
/// <returns>Указатель на интерфейс IMcWindowContainer, если создание контейнера прошло успешно, или NULL.</returns>
MECHCTL_API IMcWindowContainer* CreateDefaultIMcWindowContainer(IMcWindow *pContentWindow);

//---------------------------------------------------------------------------------------------------------------------------------------
// Системный вызов после изменения таблицы слоев
extern "C" HRESULT MECHCTL_API OnLayersTableChangedInternal();

//---------------------------------------------------------------------------------------------------------------------------------------
// Регистрация команды для контроля проектных состояний в автотестах
extern "C" HRESULT MECHCTL_API RegisterProjectSnapshot();
