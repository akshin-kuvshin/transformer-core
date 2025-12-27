// Карта соответствия между стилевыми переменными размеров и соответствующими им
// переменными в McDimensionData. Список переменных (DIM* var) взят из DimVarDefs.h

//      type       varname                 DIM* var  default value           metric def val          reserve1   reserve2
// DIMADEC
MAP_VAR(int,       m_iPrecisionAngular,    adec,     (0),                    (0),                    (),        ValidateRange(0, 8))
// DIMALT
MAP_FLG(MCSDIMSTY_BF_DIMALT,               alt,      (false),                (false),                (),        ValidateNone())
// DIMALTD
MAP_VAR(int,       m_iPrecisionAlt,        altd,     (2),                    (3),                    (),        ValidateRange(0,8))
// DIMALTF
MAP_VAR(double,    m_rFactorAlt,           altf,     (25.4),                 (0.03937007874016),     (),        ValidateRange(DBL_MIN, DBL_MAX))
// DIMALTRND
MAP_VAR(double,    m_rRoundAlt,            altrnd,   (0.0),                  (0.0),                  (),        ValidateRange(0,DBL_MAX))
// DIMALTTD
MAP_VAR(int,       m_iPrecisionTolAlt,     alttd,    (2),                    (3),                    (),        ValidateRange(0,8))
// DIMALTTZ
MAP_VAR(int,       m_iZeroSupTolAlt,       alttz,    (0),                    (0),                    (),        ValidateRange(0,15))
// DIMALTU
MAP_VAR(McsDimAltFormatting, m_eFormatAlt, altu,     (kMcsDimAltFmt_Decimal),(kMcsDimAltFmt_Decimal),(),        ValidateRange(kMcsDimAltFmt_Scientific,kMcsDimAltFmt_MSWinDesktop))
// DIMALTZ
MAP_VAR(int,       m_iZeroSupAlt,          altz,     (0),                    (0),                    (),        ValidateRange(0,15))
// DIMAPOST                DIMAPOST is in the form /prefix/<>/suffix/. "
MAP_VAR(McsString, m_strPostAlt,           apost,    (_T("")),               (_T("")),               (),        ValidateNone())
// DIMASZ
MAP_VAR(double,    m_rArrowSize,           asz,      (0.18),                 (2.5),                  (),        ValidateRange(0,DBL_MAX))
// DIMATFIT
MAP_VAR(McsDimArrowsTextFit, m_eArwTxtFit, atfit,    (kMcsDimArrowsTextFit_TextOrArrowsBestFit), (kMcsDimArrowsTextFit_TextOrArrowsBestFit), (), ValidateRange(kMcsDimArrowsTextFit_TextAndArrowsOutside,kMcsDimArrowsTextFit_TextOrArrowsBestFit))
// DIMAUNIT
MAP_VAR(McsDimAngFormatting, m_eFormatAngular, aunit, (kMcsDimAngFmt_DecimalDegrees), (kMcsDimAngFmt_DecimalDegrees), (), ValidateRange(kMcsDimAngFmt_DecimalDegrees,kMcsDimAngFmt_Surveyor))
// DIMAZIN
MAP_VAR(int,       m_iZeroSupAng,          azin,     (0),                    (0),                    (),        ValidateRange(0,3))
// DIMBLK
MAP_VAR_ArrowId(MCS_ARROW, m_McsArrowBoth, blk,      (MCS_ArrArrow),         (MCS_ArrArrow),         (),        ValidateRange(MCS_ArrUnknown, MCS_ArrArchTick))
// DIMBLK1
MAP_VAR_ArrowId(MCS_ARROW, m_McsArrow1st,  blk1,     (MCS_ArrArrow),         (MCS_ArrArrow),         (),        ValidateRange(MCS_ArrUnknown, MCS_ArrArchTick))
// DIMBLK2
MAP_VAR_ArrowId(MCS_ARROW, m_McsArrow2nd,  blk2,     (MCS_ArrArrow),         (MCS_ArrArrow),         (),        ValidateRange(MCS_ArrUnknown, MCS_ArrArchTick))
// DIMCEN
MAP_VAR(double,    m_rCenterMarks,         cen,      (0.09),                 (2.5),                  (),        ValidateNone())
// DIMCLRD
MAP_VAR_Color(COLORREF, m_crLinesDim,      clrd,     (MCS_ENTCOLOR_BYBLOCK), (MCS_ENTCOLOR_BYBLOCK), (),        ValidateColor())
// DIMCLRE
MAP_VAR_Color(COLORREF, m_crLinesExt,      clre,     (MCS_ENTCOLOR_BYBLOCK), (MCS_ENTCOLOR_BYBLOCK), (),        ValidateColor())
// DIMCLRT
MAP_VAR_Color(COLORREF, m_crTextDim,       clrt,     (MCS_ENTCOLOR_BYBLOCK), (MCS_ENTCOLOR_BYBLOCK), (),        ValidateColor())
// DIMDEC
MAP_VAR(int,       m_iPrecisionLinear,     dec,      (4),                    (2),                    (),        ValidateRange(0,8))
// DIMDLE
MAP_VAR(double,    m_rExtendLinesDim,      dle,      (0.0),                  (0.0),                  (),        ValidateRange(0,DBL_MAX))
// DIMDLI
MAP_VAR(double,    m_rDimLinesDistBased,   dli,      (0.38),                 (3.75),                 (),        ValidatePositive())
// DIMDSEP
MAP_VAR(TCHAR,     m_cDecimal,             dsep,     (_T('.')),              (_T(',')),              (),        ValidateDecSep())
// DIMEXE
MAP_VAR(double,    m_rExtendLinesExt,      exe,      (0.18),                 (1.25),                 (),        ValidatePositive())
// DIMEXO
MAP_VAR(double,    m_rExtLinesOffset,      exo,      (0.0625),               (0.625),                (),        ValidatePositive())
// DIMFRAC
MAP_VAR(McsDimFracFormatting, m_eFormatFraction, frac, (kMcsDimFracFmt_HorizontalStacked), (kMcsDimFracFmt_HorizontalStacked), (), ValidateRange(kMcsDimFracFmt_HorizontalStacked,kMcsDimFracFmt_NotStacked))
// DIMGAP
MAP_VAR(double,    m_rTextOffset,          gap,      (0.09),                 (0.625),                (),        ValidateNone())
// DIMJUST
MAP_VAR(McsDimTxtHorzPos, m_eFormatDimTxtHrzPos, just, (kMcsDimTxtHorzPos_AboveDimCentered), (kMcsDimTxtHorzPos_AboveDimCentered), (), ValidateRange(kMcsDimTxtHorzPos_AboveDimCentered,kMcsDimTxtHorzPos_AboveDimPrll2ndExt))
// DIMLDRBLK
MAP_VAR_ArrowId(MCS_ARROW, m_McsArrowLeader, ldrblk, (MCS_ArrArrow),         (MCS_ArrArrow),         (),        ValidateRange(MCS_ArrUnknown, MCS_ArrArchTick))
// DIMLFAC
MAP_VAR(double,    m_rFactor,              lfac,     (1.0),                  (1.0),                  (),        ValidateNone())
// DIMLIM
MAP_FLG(MCSDIMSTY_BF_DIMLIM,               lim,      (false),                (false),                (),        ValidateNone())
// DIMLUNIT
MAP_VAR(McsDimFormattingNonAng, m_eFormatUnitLinear, lunit, (kMcsDimFormattingNonAng_Decimal), (kMcsDimFormattingNonAng_Decimal), (), ValidateRange(kMcsDimFormattingNonAng_Scientific,kMcsDimFormattingNonAng_MSWinDesktop))
// DIMLWD
MAP_VAR_LineWeight(int, m_iLineWeightDim,  lwd,      (MCS_ENTWEIGHT_BYBLOCK),(MCS_ENTWEIGHT_BYBLOCK),(),        ValidateLineWeight())
// DIMLWE
MAP_VAR_LineWeight(int, m_iLineWeightExt,  lwe,      (MCS_ENTWEIGHT_BYBLOCK),(MCS_ENTWEIGHT_BYBLOCK),(),        ValidateLineWeight())
// DIMPOST
MAP_VAR(McsString, m_strPost,              post,     (_T("")),               (_T("")),               (),        ValidateNone())
// DIMRND
MAP_VAR(double,    m_rRound,               rnd,      (0.0),                  (0.0),                  (),        ValidatePositive())
// DIMSAH
MAP_FLG(MCSDIMSTY_BF_SEPARRHEAD,           sah,      (false),                (false),                (),        ValidateNone())
// DIMSCALE
MAP_VAR(double, m_rScale_useMcDbDimension, scale,    (1.0),                  (1.0),                  (),        ValidatePositive())
// DIMSD1
MAP_FLG(MCSDIMSTY_BF_SUPDIM1,              sd1,      (false),                (false),                (),        ValidateNone())
// DIMSD2
MAP_FLG(MCSDIMSTY_BF_SUPDIM2,              sd2,      (false),                (false),                (),        ValidateNone())
// DIMSE1
MAP_FLG(MCSDIMSTY_BF_SUPEXT1,              se1,      (false),                (false),                (),        ValidateNone())
// DIMSE2
MAP_FLG(MCSDIMSTY_BF_SUPEXT2,              se2,      (false),                (false),                (),        ValidateNone())
// DIMSOXD
MAP_FLG(MCSDIMSTY_BF_SUPDIMOX,             soxd,     (false),                (false),                (),        ValidateNone())
// DIMTAD
MAP_VAR(McsDimVertTextAlignEnum, m_dvtaVertTextAlign, tad, (kMcsDimVertTextAlign_Centered), (kMcsDimVertTextAlign_Above), (), ValidateRange(kMcsDimVertTextAlign_Centered,kMcsDimVertTextAlign_Below))
// DIMTDEC
MAP_VAR(int,       m_iPrecisionTol,        tdec,     (4),                    (2),                    (),        ValidateRange(0,8))
// DIMTFAC
MAP_VAR(double,    m_rFactorTxtTol,        tfac,     (1.0),                  (1.0),                  (),        ValidatePositiveNonZero())
// DIMTIH
MAP_FLG(MCSDIMSTY_BF_TIXORIENT,            tih,      (true),                 (false),                (),        ValidateNone())
// DIMTIX
MAP_FLG(MCSDIMSTY_BF_TIXPLACE,             tix,      (false),                (false),                (),        ValidateNone())
// DIMTM
MAP_VAR(double,    m_rTolMinus,            tm,       (0.0),                  (0.0),                  (),        ValidateNone())
// DIMTMOVE
MAP_VAR(McsDimTextMovement, m_eMoveTextBehavior, tmove, (kMcsDimTextMovement_TextMovesDimLine), (kMcsDimTextMovement_TextMovesDimLine), (), ValidateRange(kMcsDimTextMovement_TextMovesDimLine,kMcsDimTextMovement_TextDoesntAddLeader))
// DIMTOFL
MAP_FLG(MCSDIMSTY_BF_TOFL,                 tofl,     (false),                (true),                 (),        ValidateNone())
// DIMTOH
MAP_FLG(MCSDIMSTY_BF_TOXTXTORI,            toh,      (true),                 (false),                (),        ValidateNone())
// DIMTOL
MAP_FLG(MCSDIMSTY_BF_TOL,                  tol,      (false),                (false),                (),        ValidateNone())
// DIMTOLJ
MAP_VAR(McsDimTolVertJustifyEnum, m_eJustVertTol, tolj, (kMcsDimTolVertJustify_Middle), (kMcsDimTolVertJustify_Bottom), (), ValidateRange(kMcsDimTolVertJustify_Bottom,kMcsDimTolVertJustify_Top))
// DIMTP
MAP_VAR(double,    m_rTolPlus,             tp,       (0.0),                  (0.0),                  (),        ValidateNone())
// DIMTSZ
MAP_VAR(double,    m_rTickSize,            tsz,      (0.0),                  (0.0),                  (),        ValidatePositive())
// DIMTVP
MAP_VAR(double,    m_rTextVP,              tvp,      (0.0),                  (0.0),                  (),        ValidateNone())
// DIMTXSTY // ValidateTextStyle(NullIdAllowed)
MAP_VAR_StyleId(McsString, m_strTxtStyle,  txsty,    (_T("")),               (_T("")),               (),        ValidateNone())
// DIMTXT
MAP_VAR(double,    m_rTextHeight,          txt,      (0.18),                 (2.5),                  (),        ValidatePositiveNonZero())
// DIMTZIN
MAP_VAR(int,       m_iZeroSupLinTol,       tzin,     (0),                    (8),                    (),        ValidateRange(0,15))
// DIMUPT
MAP_FLG(MCSDIMSTY_BF_DIMUPT,               upt,      (false),                (false),                (),        ValidateNone())
// DIMZIN
MAP_VAR(int,       m_iZeroSupLin,          zin,      (0),                    (8),                    (),        ValidateRange(0,15))
// DIMFXL
MAP_VAR(double,    m_rFixLenExtLength,     fxl,      (1.0),                  (1.0),                  (),        ValidateNone())
// DIMFXLON
MAP_FLG(MCSDIMSTY_BF_FXLON,                fxlon,    (false),                (false),                (),        ValidateBOOL())
// DIMJOGANG // валидация от 5 до 90 градусов
MAP_VAR(double,    m_rJogAngle,            jogang,   (PI/4.0),               (PI/4.0),               (),        ValidateDouble(PI/36.0, PI/2.0))
// DIMTFILL
MAP_VAR(McsDimTextFill, m_eDimTxtFillBG,   tfill,    (kMcsDimTextFill_NoFill), (kMcsDimTextFill_NoFill), (),    ValidateRange(kMcsDimTextFill_NoFill, kMcsDimTextFill_ByDIMTFILLCLR))
// DIMTFILLCLR
MAP_VAR_Color(COLORREF, m_crDimTxtFillBG,  tfillclr, (MCS_ENTCOLOR_BYBLOCK), (MCS_ENTCOLOR_BYBLOCK), (),        ValidateColor())
// DIMARCSYM
MAP_VAR(McsArcSymbolPos, m_eArcSymbolPos,  arcsym,   (kMcsArcSymbolPos_BeforeDimText), (kMcsArcSymbolPos_BeforeDimText), (), ValidateRange(kMcsArcSymbolPos_BeforeDimText, kMcsArcSymbolPos_NotDisplayed))
// DIMLTYPE
MAP_VAR_LineTypeId(DWORD, m_dwLineTypeDim, ltype,    (MCS_ENTLTYPE_BYBLOCK), (MCS_ENTLTYPE_BYBLOCK), (),        ValidateLinetype(true))
// DIMLTEX1
MAP_VAR_LineTypeId(DWORD, m_dwLineTypeExt1,ltex1,    (MCS_ENTLTYPE_BYBLOCK), (MCS_ENTLTYPE_BYBLOCK), (),        ValidateLinetype(true))
// DIMLTEX2
MAP_VAR_LineTypeId(DWORD, m_dwLineTypeExt2,ltex2,    (MCS_ENTLTYPE_BYBLOCK), (MCS_ENTLTYPE_BYBLOCK), (),        ValidateLinetype(true))
// DIMTXTDIRECTION
MAP_FLG(MCSDIMSTY_BF_TXTDIR,           txtdirection, (false),                (false),                (),        ValidateBOOL())
// DIMMZF
MAP_VAR(double,    m_rDimMzf,              mzf,      (100.0),                (100.0),                (),        ValidateNone())
// DIMMZS
MAP_VAR(McsString, m_strDimMzs,            mzs,      (_T("")),               (_T("")),               (),        ValidateNone())
// DIMALTMZF
MAP_VAR(double,    m_rDimAltMzf,           altmzf,   (100.0),                (100.0),                (),        ValidateNone())
// DIMALTMZS
MAP_VAR(McsString, m_strDimAltMzs,         altmzs,   (_T("")),               (_T("")),               (),        ValidateNone())
