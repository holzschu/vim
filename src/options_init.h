/* vi:set ts=8 sts=4 sw=4 noet:
 *
 * VIM - Vi IMproved	by Bram Moolenaar
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 */

/*
 * optiondefs.h: option definitions
 */

// The options that are local to a window or buffer have "indir" set to one of
// these values.  Special values:
// PV_NONE: global option.
// PV_WIN is added: window-local option
// PV_BUF is added: buffer-local option
// PV_BOTH is added: global option which also has a local value.
// options[] is initialized here.
// The order of the options MUST be alphabetic for ":set all" and findoption().
// All option names MUST start with a lowercase letter (for findoption()).
// Exception: "t_" options are at the end.
// The options with a NULL variable are 'hidden': a set command for them is
// ignored and they are not printed.
// 
// iOS: re-initialize all options
// static __thread struct vimoption options[] = {
options[0] = (struct vimoption) {"aleph",	    "al",   P_NUM|P_VI_DEF|P_CURSWANT,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)&p_aleph, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {
#if defined(MSWIN) && !defined(FEAT_GUI_MSWIN)
			    (char_u *)128L,
#else
			    (char_u *)224L,
#endif
					    (char_u *)0L} SCTX_INIT},
options[1] = (struct vimoption) {"antialias",   "anti", P_BOOL|P_VI_DEF|P_VIM|P_RCLR,
#if defined(FEAT_GUI_MAC)
			    (char_u *)&p_antialias, PV_NONE,
			    {(char_u *)FALSE, (char_u *)FALSE}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)FALSE}
#endif
			    SCTX_INIT},
options[2] = (struct vimoption) {"arabic",	    "arab", P_BOOL|P_VI_DEF|P_VIM|P_CURSWANT,
#ifdef FEAT_ARABIC
			    (char_u *)VAR_WIN, PV_ARAB,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[3] = (struct vimoption) {"arabicshape", "arshape", P_BOOL|P_VI_DEF|P_VIM|P_RCLR,
#ifdef FEAT_ARABIC
			    (char_u *)&p_arshape, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[4] = (struct vimoption) {"allowrevins", "ari",  P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)&p_ari, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[5] = (struct vimoption) {"altkeymap",   "akm",  P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[6] = (struct vimoption) {"ambiwidth",  "ambw",  P_STRING|P_VI_DEF|P_RCLR,
			    (char_u *)&p_ambw, PV_NONE,
			    {(char_u *)"single", (char_u *)0L}
			    SCTX_INIT},
options[7] = (struct vimoption) {"autochdir",  "acd",   P_BOOL|P_VI_DEF,
#ifdef FEAT_AUTOCHDIR
			    (char_u *)&p_acd, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[8] = (struct vimoption) {"autoshelldir",  "asd",   P_BOOL|P_VI_DEF,
#ifdef FEAT_AUTOSHELLDIR
			    (char_u *)&p_asd, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[9] = (struct vimoption) {"autoindent",  "ai",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_ai, PV_AI,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[10] = (struct vimoption) {"autoprint",   "ap",   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[11] = (struct vimoption) {"autoread",    "ar",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_ar, PV_AR,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[12] = (struct vimoption) {"autowrite",   "aw",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_aw, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[13] = (struct vimoption) {"autowriteall","awa",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_awa, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[14] = (struct vimoption) {"background",  "bg",   P_STRING|P_VI_DEF|P_RCLR,
			    (char_u *)&p_bg, PV_NONE,
			    {
#if (defined(MSWIN)) && !defined(FEAT_GUI)
			    (char_u *)"dark",
#else
			    (char_u *)"light",
#endif
					    (char_u *)0L} SCTX_INIT},
options[15] = (struct vimoption) {"backspace",   "bs",   P_STRING|P_VI_DEF|P_VIM|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_bs, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[16] = (struct vimoption) {"backup",	    "bk",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_bk, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[17] = (struct vimoption) {"backupcopy",  "bkc",  P_STRING|P_VIM|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_bkc, PV_BKC,
#ifdef UNIX
			    {(char_u *)"yes", (char_u *)"auto"}
#else
			    {(char_u *)"auto", (char_u *)"auto"}
#endif
			    SCTX_INIT},
options[18] = (struct vimoption) {"backupdir",   "bdir", P_STRING|P_EXPAND|P_VI_DEF|P_ONECOMMA
							    |P_NODUP|P_SECURE,
			    (char_u *)&p_bdir, PV_NONE,
			    {(char_u *)DFLT_BDIR, (char_u *)0L} SCTX_INIT},
options[19] = (struct vimoption) {"backupext",   "bex",  P_STRING|P_VI_DEF|P_NFNAME,
			    (char_u *)&p_bex, PV_NONE,
			    {
#ifdef VMS
			    (char_u *)"_",
#else
			    (char_u *)"~",
#endif
					    (char_u *)0L} SCTX_INIT},
options[20] = (struct vimoption) {"backupskip",  "bsk",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_WILDIGN
			    (char_u *)&p_bsk, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[21] = (struct vimoption) {"balloondelay","bdlay",P_NUM|P_VI_DEF,
#ifdef FEAT_BEVAL
			    (char_u *)&p_bdlay, PV_NONE,
			    {(char_u *)600L, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[22] = (struct vimoption) {"ballooneval", "beval",P_BOOL|P_VI_DEF|P_NO_MKRC,
#ifdef FEAT_BEVAL_GUI
			    (char_u *)&p_beval, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[23] = (struct vimoption) {"balloonevalterm", "bevalterm",P_BOOL|P_VI_DEF|P_NO_MKRC,
#ifdef FEAT_BEVAL_TERM
			    (char_u *)&p_bevalterm, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[24] = (struct vimoption) {"balloonexpr", "bexpr", P_STRING|P_ALLOCED|P_VI_DEF|P_VIM|P_MLE,
#if defined(FEAT_BEVAL) && defined(FEAT_EVAL)
			    (char_u *)&p_bexpr, PV_BEXPR,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[25] = (struct vimoption) {"beautify",    "bf",   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[26] = (struct vimoption) {"belloff",      "bo",  P_STRING|P_VI_DEF|P_COMMA|P_NODUP,
			    (char_u *)&p_bo, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[27] = (struct vimoption) {"binary",	    "bin",  P_BOOL|P_VI_DEF|P_RSTAT,
			    (char_u *)&p_bin, PV_BIN,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[28] = (struct vimoption) {"bioskey",	    "biosk",P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[29] = (struct vimoption) {"bomb",	    NULL,   P_BOOL|P_NO_MKRC|P_VI_DEF|P_RSTAT,
			    (char_u *)&p_bomb, PV_BOMB,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[30] = (struct vimoption) {"breakat",	    "brk",  P_STRING|P_VI_DEF|P_RALL|P_FLAGLIST,
#ifdef FEAT_LINEBREAK
			    (char_u *)&p_breakat, PV_NONE,
			    {(char_u *)" \t!@*-+;:,./?", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[31] = (struct vimoption) {"breakindent",   "bri",  P_BOOL|P_VI_DEF|P_VIM|P_RWIN,
#ifdef FEAT_LINEBREAK
			    (char_u *)VAR_WIN, PV_BRI,
			    {(char_u *)FALSE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[32] = (struct vimoption) {"breakindentopt", "briopt", P_STRING|P_ALLOCED|P_VI_DEF|P_RBUF
						  |P_ONECOMMA|P_NODUP,
#ifdef FEAT_LINEBREAK
			    (char_u *)VAR_WIN, PV_BRIOPT,
			    {(char_u *)"", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
#endif
			    SCTX_INIT},
options[33] = (struct vimoption) {"browsedir",   "bsdir",P_STRING|P_VI_DEF,
#ifdef FEAT_BROWSE
			    (char_u *)&p_bsdir, PV_NONE,
			    {(char_u *)"last", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[34] = (struct vimoption) {"bufhidden",   "bh",   P_STRING|P_ALLOCED|P_VI_DEF|P_NOGLOB,
			    (char_u *)&p_bh, PV_BH,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[35] = (struct vimoption) {"buflisted",   "bl",   P_BOOL|P_VI_DEF|P_NOGLOB,
			    (char_u *)&p_bl, PV_BL,
			    {(char_u *)1L, (char_u *)0L}
			    SCTX_INIT},
options[36] = (struct vimoption) {"buftype",	    "bt",   P_STRING|P_ALLOCED|P_VI_DEF|P_NOGLOB,
			    (char_u *)&p_bt, PV_BT,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[37] = (struct vimoption) {"casemap",	    "cmp",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cmp, PV_NONE,
			    {(char_u *)"internal,keepascii", (char_u *)0L}
			    SCTX_INIT},
options[38] = (struct vimoption) {"cdhome",	    "cdh",  P_BOOL|P_VI_DEF|P_VIM|P_SECURE,
			    (char_u *)&p_cdh, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L}
			    SCTX_INIT},
options[39] = (struct vimoption) {"cdpath",	    "cd",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE|P_COMMA|P_NODUP,
#ifdef FEAT_SEARCHPATH
			    (char_u *)&p_cdpath, PV_NONE,
			    {(char_u *)",,", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[40] = (struct vimoption) {"cedit",	    NULL,   P_STRING,
#ifdef FEAT_CMDWIN
			    (char_u *)&p_cedit, PV_NONE,
			    {(char_u *)"", (char_u *)CTRL_F_STR}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[41] = (struct vimoption) {"charconvert",  "ccv", P_STRING|P_VI_DEF|P_SECURE,
#if defined(FEAT_EVAL)
			    (char_u *)&p_ccv, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[42] = (struct vimoption) {"cindent",	    "cin",  P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_cin, PV_CIN,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[43] = (struct vimoption) {"cinkeys",	    "cink", P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cink, PV_CINK,
			    {INDENTKEYS_DEFAULT, (char_u *)0L} SCTX_INIT},
options[44] = (struct vimoption) {"cinoptions",  "cino", P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cino, PV_CINO,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[45] = (struct vimoption) {"cinscopedecls", "cinsd", P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cinsd, PV_CINSD,
			    {(char_u *)"public,protected,private", (char_u *)0L}
			    SCTX_INIT},
options[46] = (struct vimoption) {"cinwords",    "cinw", P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cinw, PV_CINW,
			    {(char_u *)"if,else,while,do,for,switch",
				(char_u *)0L}
			    SCTX_INIT},
options[47] = (struct vimoption) {"clipboard",   "cb",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_CLIPBOARD
			    (char_u *)&p_cb, PV_NONE,
# ifdef FEAT_XCLIPBOARD
			    {(char_u *)"autoselect,exclude:cons\\|linux",
							       (char_u *)0L}
# else
			    {(char_u *)"", (char_u *)0L}
# endif
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#endif
			    SCTX_INIT},
options[48] = (struct vimoption) {"cmdheight",   "ch",   P_NUM|P_VI_DEF|P_RALL,
			    (char_u *)&p_ch, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[49] = (struct vimoption) {"cmdwinheight", "cwh", P_NUM|P_VI_DEF,
#ifdef FEAT_CMDWIN
			    (char_u *)&p_cwh, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)7L, (char_u *)0L} SCTX_INIT},
options[50] = (struct vimoption) {"colorcolumn", "cc",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP|P_RWIN,
#ifdef FEAT_SYN_HL
			    (char_u *)VAR_WIN, PV_CC,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[51] = (struct vimoption) {"columns",	    "co",   P_NUM|P_NODEFAULT|P_NO_MKRC|P_VI_DEF|P_RCLR,
			    (char_u *)&Columns, PV_NONE,
			    {(char_u *)80L, (char_u *)0L} SCTX_INIT},
options[52] = (struct vimoption) {"comments",    "com",  P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA
							  |P_NODUP|P_CURSWANT,
			    (char_u *)&p_com, PV_COM,
			    {(char_u *)"s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-",
				(char_u *)0L}
			    SCTX_INIT},
options[53] = (struct vimoption) {"commentstring", "cms", P_STRING|P_ALLOCED|P_VI_DEF|P_CURSWANT,
#ifdef FEAT_FOLDING
			    (char_u *)&p_cms, PV_CMS,
			    {(char_u *)"/*%s*/", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
			    // P_PRI_MKRC isn't needed here, optval_default()
			    // always returns TRUE for 'compatible'
options[54] = (struct vimoption) {"compatible",  "cp",   P_BOOL|P_RALL,
			    (char_u *)&p_cp, PV_NONE,
			    {(char_u *)TRUE, (char_u *)FALSE} SCTX_INIT},
options[55] = (struct vimoption) {"complete",    "cpt",  P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cpt, PV_CPT,
			    {(char_u *)".,w,b,u,t,i", (char_u *)0L}
			    SCTX_INIT},
options[56] = (struct vimoption) {"concealcursor","cocu", P_STRING|P_ALLOCED|P_RWIN|P_VI_DEF,
#ifdef FEAT_CONCEAL
			    (char_u *)VAR_WIN, PV_COCU,
			    {(char_u *)"", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[57] = (struct vimoption) {"conceallevel","cole", P_NUM|P_RWIN|P_VI_DEF,
#ifdef FEAT_CONCEAL
			    (char_u *)VAR_WIN, PV_COLE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L}
			    SCTX_INIT},
options[58] = (struct vimoption) {"completefunc", "cfu", P_STRING|P_ALLOCED|P_VI_DEF|P_SECURE|P_FUNC,
#ifdef FEAT_COMPL_FUNC
			    (char_u *)&p_cfu, PV_CFU,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[59] = (struct vimoption) {"completeopt",   "cot",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_cot, PV_NONE,
			    {(char_u *)"menu,preview", (char_u *)0L}
			    SCTX_INIT},
options[60] = (struct vimoption) {"completepopup", "cpp", P_STRING|P_VI_DEF|P_COMMA|P_NODUP,
#if defined(FEAT_PROP_POPUP) && defined(FEAT_QUICKFIX)
			    (char_u *)&p_cpp, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[61] = (struct vimoption) {"completeslash",   "csl",  P_STRING|P_VI_DEF|P_VIM,
#if defined(BACKSLASH_IN_FILENAME)
			    (char_u *)&p_csl, PV_CSL,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[62] = (struct vimoption) {"confirm",     "cf",   P_BOOL|P_VI_DEF,
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
			    (char_u *)&p_confirm, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[63] = (struct vimoption) {"conskey",	    "consk",P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[64] = (struct vimoption) {"copyindent",  "ci",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_ci, PV_CI,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[65] = (struct vimoption) {"cpoptions",   "cpo",  P_STRING|P_VIM|P_RALL|P_FLAGLIST,
			    (char_u *)&p_cpo, PV_NONE,
			    {(char_u *)CPO_VI, (char_u *)CPO_VIM}
			    SCTX_INIT},
options[66] = (struct vimoption) {"cryptmethod", "cm",   P_STRING|P_ALLOCED|P_VI_DEF,
#ifdef FEAT_CRYPT
			    (char_u *)&p_cm, PV_CM,
			    {(char_u *)"blowfish2", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[67] = (struct vimoption) {"cscopepathcomp", "cspc", P_NUM|P_VI_DEF|P_VIM,
#ifdef FEAT_CSCOPE
			    (char_u *)&p_cspc, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[68] = (struct vimoption) {"cscopeprg",   "csprg", P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#ifdef FEAT_CSCOPE
			    (char_u *)&p_csprg, PV_NONE,
			    {(char_u *)"cscope", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[69] = (struct vimoption) {"cscopequickfix", "csqf", P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#if defined(FEAT_CSCOPE) && defined(FEAT_QUICKFIX)
			    (char_u *)&p_csqf, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[70] = (struct vimoption) {"cscoperelative", "csre", P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_CSCOPE
			    (char_u *)&p_csre, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[71] = (struct vimoption) {"cscopetag",   "cst",  P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_CSCOPE
			    (char_u *)&p_cst, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[72] = (struct vimoption) {"cscopetagorder", "csto", P_NUM|P_VI_DEF|P_VIM,
#ifdef FEAT_CSCOPE
			    (char_u *)&p_csto, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[73] = (struct vimoption) {"cscopeverbose", "csverb", P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_CSCOPE
			    (char_u *)&p_csverbose, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[74] = (struct vimoption) {"cursorbind",  "crb",  P_BOOL|P_VI_DEF,
			    (char_u *)VAR_WIN, PV_CRBIND,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[75] = (struct vimoption) {"cursorcolumn", "cuc", P_BOOL|P_VI_DEF|P_RWINONLY,
#ifdef FEAT_SYN_HL
			    (char_u *)VAR_WIN, PV_CUC,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[76] = (struct vimoption) {"cursorline",   "cul", P_BOOL|P_VI_DEF|P_RWINONLY,
#ifdef FEAT_SYN_HL
			    (char_u *)VAR_WIN, PV_CUL,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[77] = (struct vimoption) {"cursorlineopt", "culopt", P_STRING|P_VI_DEF|P_RWIN|P_ONECOMMA|P_NODUP,
#ifdef FEAT_SYN_HL
			    (char_u *)VAR_WIN, PV_CULOPT,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"both", (char_u *)0L} SCTX_INIT},
options[78] = (struct vimoption) {"debug",	    NULL,   P_STRING|P_VI_DEF,
			    (char_u *)&p_debug, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[79] = (struct vimoption) {"define",	    "def",  P_STRING|P_ALLOCED|P_VI_DEF|P_CURSWANT,
#ifdef FEAT_FIND_ID
			    (char_u *)&p_def, PV_DEF,
			    {(char_u *)"^\\s*#\\s*define", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[80] = (struct vimoption) {"delcombine", "deco",  P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_deco, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[81] = (struct vimoption) {"dictionary",  "dict", P_STRING|P_EXPAND|P_VI_DEF|P_ONECOMMA|P_NODUP|P_NDNAME,
			    (char_u *)&p_dict, PV_DICT,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[82] = (struct vimoption) {"diff",	    NULL,   P_BOOL|P_VI_DEF|P_RWIN|P_NOGLOB,
#ifdef FEAT_DIFF
			    (char_u *)VAR_WIN, PV_DIFF,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[83] = (struct vimoption) {"diffexpr",    "dex",  P_STRING|P_VI_DEF|P_SECURE|P_CURSWANT,
#if defined(FEAT_DIFF) && defined(FEAT_EVAL)
			    (char_u *)&p_dex, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[84] = (struct vimoption) {"diffopt",	    "dip",  P_STRING|P_ALLOCED|P_VI_DEF|P_RWIN|P_ONECOMMA
								     |P_NODUP,
#ifdef FEAT_DIFF
			    (char_u *)&p_dip, PV_NONE,
			    {(char_u *)"internal,filler,closeoff",
								(char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
#endif
			    SCTX_INIT},
options[85] = (struct vimoption) {"digraph",	    "dg",   P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_DIGRAPHS
			    (char_u *)&p_dg, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[86] = (struct vimoption) {"directory",   "dir",  P_STRING|P_EXPAND|P_VI_DEF|P_ONECOMMA
							    |P_NODUP|P_SECURE,
			    (char_u *)&p_dir, PV_NONE,
			    {(char_u *)DFLT_DIR, (char_u *)0L} SCTX_INIT},
options[87] = (struct vimoption) {"display",	    "dy",   P_STRING|P_VI_DEF|P_ONECOMMA|P_RALL|P_NODUP,
			    (char_u *)&p_dy, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[88] = (struct vimoption) {"eadirection", "ead",  P_STRING|P_VI_DEF,
			    (char_u *)&p_ead, PV_NONE,
			    {(char_u *)"both", (char_u *)0L}
			    SCTX_INIT},
options[89] = (struct vimoption) {"edcompatible","ed",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_ed, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[90] = (struct vimoption) {"emoji",  "emo",	    P_BOOL|P_VI_DEF|P_RCLR,
			    (char_u *)&p_emoji, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L}
			    SCTX_INIT},
options[91] = (struct vimoption) {"encoding",    "enc",  P_STRING|P_VI_DEF|P_RCLR|P_NO_ML,
			    (char_u *)&p_enc, PV_NONE,
			    {(char_u *)ENC_DFLT, (char_u *)0L}
			    SCTX_INIT},
options[92] = (struct vimoption) {"endofline",   "eol",  P_BOOL|P_NO_MKRC|P_VI_DEF|P_RSTAT,
			    (char_u *)&p_eol, PV_EOL,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[93] = (struct vimoption) {"equalalways", "ea",   P_BOOL|P_VI_DEF|P_RALL,
			    (char_u *)&p_ea, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[94] = (struct vimoption) {"equalprg",    "ep",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
			    (char_u *)&p_ep, PV_EP,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[95] = (struct vimoption) {"errorbells",  "eb",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_eb, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[96] = (struct vimoption) {"errorfile",   "ef",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_ef, PV_NONE,
			    {(char_u *)DFLT_ERRORFILE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[97] = (struct vimoption) {"errorformat", "efm",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_efm, PV_EFM,
			    {(char_u *)DFLT_EFM, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[98] = (struct vimoption) {"esckeys",	    "ek",   P_BOOL|P_VIM,
			    (char_u *)&p_ek, PV_NONE,
			    {(char_u *)FALSE, (char_u *)TRUE} SCTX_INIT},
options[99] = (struct vimoption) {"eventignore", "ei",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_ei, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[100] = (struct vimoption) {"expandtab",   "et",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_et, PV_ET,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[101] = (struct vimoption) {"exrc",	    "ex",   P_BOOL|P_VI_DEF|P_SECURE,
			    (char_u *)&p_exrc, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[102] = (struct vimoption) {"fileencoding","fenc", P_STRING|P_ALLOCED|P_VI_DEF|P_RSTAT|P_RBUF
								   |P_NO_MKRC,
			    (char_u *)&p_fenc, PV_FENC,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[103] = (struct vimoption) {"fileencodings","fencs", P_STRING|P_VI_DEF|P_ONECOMMA,
			    (char_u *)&p_fencs, PV_NONE,
			    {(char_u *)"ucs-bom", (char_u *)0L}
			    SCTX_INIT},
options[104] = (struct vimoption) {"fileformat",  "ff",   P_STRING|P_ALLOCED|P_VI_DEF|P_RSTAT|P_NO_MKRC
								  |P_CURSWANT,
			    (char_u *)&p_ff, PV_FF,
			    {(char_u *)DFLT_FF, (char_u *)0L} SCTX_INIT},
options[105] = (struct vimoption) {"fileformats", "ffs",  P_STRING|P_VIM|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_ffs, PV_NONE,
			    {(char_u *)DFLT_FFS_VI, (char_u *)DFLT_FFS_VIM}
			    SCTX_INIT},
options[106] = (struct vimoption) {"fileignorecase", "fic", P_BOOL|P_VI_DEF,
			    (char_u *)&p_fic, PV_NONE,
			    {
#ifdef CASE_INSENSITIVE_FILENAME
				    (char_u *)TRUE,
#else
				    (char_u *)FALSE,
#endif
					(char_u *)0L} SCTX_INIT},
options[107] = (struct vimoption) {"filetype",    "ft",   P_STRING|P_ALLOCED|P_VI_DEF|P_NOGLOB|P_NFNAME,
			    (char_u *)&p_ft, PV_FT,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[108] = (struct vimoption) {"fillchars",   "fcs",  P_STRING|P_VI_DEF|P_RALL|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_fcs, PV_NONE,
			    {(char_u *)"vert:|,fold:-,eob:~", (char_u *)0L}
			    SCTX_INIT},
options[109] = (struct vimoption) {"fixendofline",  "fixeol", P_BOOL|P_VI_DEF|P_RSTAT,
			    (char_u *)&p_fixeol, PV_FIXEOL,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[110] = (struct vimoption) {"fkmap",	    "fk",   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[111] = (struct vimoption) {"flash",	    "fl",   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[112] = (struct vimoption) {"foldclose",   "fcl",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)&p_fcl, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[113] = (struct vimoption) {"foldcolumn",  "fdc",  P_NUM|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FDC,
			    {(char_u *)FALSE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[114] = (struct vimoption) {"foldenable",  "fen",  P_BOOL|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FEN,
			    {(char_u *)TRUE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[115] = (struct vimoption) {"foldexpr",    "fde",  P_STRING|P_ALLOCED|P_VIM|P_VI_DEF|P_RWIN|P_MLE,
#if defined(FEAT_FOLDING) && defined(FEAT_EVAL)
			    (char_u *)VAR_WIN, PV_FDE,
			    {(char_u *)"0", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[116] = (struct vimoption) {"foldignore",  "fdi",  P_STRING|P_ALLOCED|P_VIM|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FDI,
			    {(char_u *)"#", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[117] = (struct vimoption) {"foldlevel",   "fdl",  P_NUM|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FDL,
			    {(char_u *)0L, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[118] = (struct vimoption) {"foldlevelstart","fdls", P_NUM|P_VI_DEF|P_CURSWANT,
#ifdef FEAT_FOLDING
			    (char_u *)&p_fdls, PV_NONE,
			    {(char_u *)-1L, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[119] = (struct vimoption) {"foldmarker",  "fmr",  P_STRING|P_ALLOCED|P_VIM|P_VI_DEF|
						    P_RWIN|P_ONECOMMA|P_NODUP,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FMR,
			    {(char_u *)"{{{,}}}", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[120] = (struct vimoption) {"foldmethod",  "fdm",  P_STRING|P_ALLOCED|P_VIM|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FDM,
			    {(char_u *)"manual", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[121] = (struct vimoption) {"foldminlines","fml",  P_NUM|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FML,
			    {(char_u *)1L, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[122] = (struct vimoption) {"foldnestmax", "fdn",  P_NUM|P_VI_DEF|P_RWIN,
#ifdef FEAT_FOLDING
			    (char_u *)VAR_WIN, PV_FDN,
			    {(char_u *)20L, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[123] = (struct vimoption) {"foldopen",    "fdo",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP|P_CURSWANT,
#ifdef FEAT_FOLDING
			    (char_u *)&p_fdo, PV_NONE,
		 {(char_u *)"block,hor,mark,percent,quickfix,search,tag,undo",
						 (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[124] = (struct vimoption) {"foldtext",    "fdt",  P_STRING|P_ALLOCED|P_VIM|P_VI_DEF|P_RWIN|P_MLE,
#if defined(FEAT_FOLDING) && defined(FEAT_EVAL)
			    (char_u *)VAR_WIN, PV_FDT,
			    {(char_u *)"foldtext()", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[125] = (struct vimoption) {"formatexpr", "fex",   P_STRING|P_ALLOCED|P_VI_DEF|P_VIM|P_MLE,
#ifdef FEAT_EVAL
			    (char_u *)&p_fex, PV_FEX,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[126] = (struct vimoption) {"formatoptions","fo",  P_STRING|P_ALLOCED|P_VIM|P_FLAGLIST,
			    (char_u *)&p_fo, PV_FO,
			    {(char_u *)DFLT_FO_VI, (char_u *)DFLT_FO_VIM}
			    SCTX_INIT},
options[127] = (struct vimoption) {"formatlistpat","flp", P_STRING|P_ALLOCED|P_VI_DEF,
			    (char_u *)&p_flp, PV_FLP,
			    {(char_u *)"^\\s*\\d\\+[\\]:.)}\\t ]\\s*",
						 (char_u *)0L} SCTX_INIT},
options[128] = (struct vimoption) {"formatprg",   "fp",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
			    (char_u *)&p_fp, PV_FP,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[129] = (struct vimoption) {"fsync",       "fs",   P_BOOL|P_SECURE|P_VI_DEF,
#ifdef HAVE_FSYNC
			    (char_u *)&p_fs, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L}
#endif
			    SCTX_INIT},
options[130] = (struct vimoption) {"gdefault",    "gd",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_gd, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[131] = (struct vimoption) {"graphic",	    "gr",   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[132] = (struct vimoption) {"grepformat",  "gfm",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_gefm, PV_NONE,
			    {(char_u *)DFLT_GREPFORMAT, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[133] = (struct vimoption) {"grepprg",	    "gp",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_gp, PV_GP,
			    {
# if defined(MSWIN)
			    // may be changed to "grep -n" in os_win32.c
			    (char_u *)"findstr /n",
# elif defined(UNIX)
			    // Add an extra file name so that grep will always
			    // insert a file name in the match line.
			    (char_u *)"grep -n $* /dev/null",
# elif defined(VMS)
			    (char_u *)"SEARCH/NUMBERS ",
# else
			    (char_u *)"grep -n ",
# endif
			    (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[134] = (struct vimoption) {"guicursor",    "gcr", P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef CURSOR_SHAPE
			    (char_u *)&p_guicursor, PV_NONE,
			    {
# ifdef FEAT_GUI
				(char_u *)"n-v-c:block-Cursor/lCursor,ve:ver35-Cursor,o:hor50-Cursor,i-ci:ver25-Cursor/lCursor,r-cr:hor20-Cursor/lCursor,sm:block-Cursor-blinkwait175-blinkoff150-blinkon175",
# else	// Win32 console
				(char_u *)"n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block",
# endif
				    (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[135] = (struct vimoption) {"guifont",	    "gfn",  P_STRING|P_VI_DEF|P_RCLR|P_ONECOMMA|P_NODUP,
#ifdef FEAT_GUI
			    (char_u *)&p_guifont, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[136] = (struct vimoption) {"guifontset",  "gfs",  P_STRING|P_VI_DEF|P_RCLR|P_ONECOMMA,
#if defined(FEAT_GUI) && defined(FEAT_XFONTSET)
			    (char_u *)&p_guifontset, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[137] = (struct vimoption) {"guifontwide", "gfw",  P_STRING|P_VI_DEF|P_RCLR|P_ONECOMMA|P_NODUP,
#if defined(FEAT_GUI)
			    (char_u *)&p_guifontwide, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},


options[138] = (struct vimoption) {"guiligatures", "gli", P_STRING|P_VI_DEF|P_RCLR|P_ONECOMMA|P_NODUP,
#if defined(FEAT_GUI_GTK)
			    (char_u *)&p_guiligatures, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},


options[139] = (struct vimoption) {"guiheadroom", "ghr",  P_NUM|P_VI_DEF,
#if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_X11)
			    (char_u *)&p_ghr, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)50L, (char_u *)0L} SCTX_INIT},
options[140] = (struct vimoption) {"guioptions",  "go",   P_STRING|P_VI_DEF|P_RALL|P_FLAGLIST,
#if defined(FEAT_GUI)
			    (char_u *)&p_go, PV_NONE,
# if defined(UNIX)
			    {(char_u *)"aegimrLtT", (char_u *)0L}
# else
			    {(char_u *)"egmrLtT", (char_u *)0L}
# endif
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[141] = (struct vimoption) {"guipty",	    NULL,   P_BOOL|P_VI_DEF,
#if defined(FEAT_GUI)
			    (char_u *)&p_guipty, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[142] = (struct vimoption) {"guitablabel",  "gtl", P_STRING|P_VI_DEF|P_RWIN|P_MLE,
#if defined(FEAT_GUI_TABLINE)
			    (char_u *)&p_gtl, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[143] = (struct vimoption) {"guitabtooltip",  "gtt", P_STRING|P_VI_DEF|P_RWIN,
#if defined(FEAT_GUI_TABLINE)
			    (char_u *)&p_gtt, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[144] = (struct vimoption) {"hardtabs",    "ht",   P_NUM|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[145] = (struct vimoption) {"helpfile",    "hf",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
			    (char_u *)&p_hf, PV_NONE,
			    {(char_u *)DFLT_HELPFILE, (char_u *)0L}
			    SCTX_INIT},
options[146] = (struct vimoption) {"helpheight",  "hh",   P_NUM|P_VI_DEF,
			    (char_u *)&p_hh, PV_NONE,
			    {(char_u *)20L, (char_u *)0L} SCTX_INIT},
options[147] = (struct vimoption) {"helplang",    "hlg",  P_STRING|P_VI_DEF|P_ONECOMMA,
#ifdef FEAT_MULTI_LANG
			    (char_u *)&p_hlg, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[148] = (struct vimoption) {"hidden",	    "hid",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_hid, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[149] = (struct vimoption) {"highlight",   "hl",   P_STRING|P_VI_DEF|P_RCLR|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_hl, PV_NONE,
			    {(char_u *)HIGHLIGHT_INIT, (char_u *)0L}
			    SCTX_INIT},
options[150] = (struct vimoption) {"history",	    "hi",   P_NUM|P_VIM,
			    (char_u *)&p_hi, PV_NONE,
			    {(char_u *)0L, (char_u *)50L} SCTX_INIT},
options[151] = (struct vimoption) {"hkmap",	    "hk",   P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)&p_hkmap, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[152] = (struct vimoption) {"hkmapp",	    "hkp",  P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)&p_hkmapp, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[153] = (struct vimoption) {"hlsearch",    "hls",  P_BOOL|P_VI_DEF|P_VIM|P_RALL,
			    (char_u *)&p_hls, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[154] = (struct vimoption) {"icon",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_icon, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[155] = (struct vimoption) {"iconstring",  NULL,   P_STRING|P_VI_DEF|P_MLE,
			    (char_u *)&p_iconstring, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[156] = (struct vimoption) {"ignorecase",  "ic",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_ic, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[157] = (struct vimoption) {"imactivatefunc","imaf",P_STRING|P_VI_DEF|P_SECURE|P_FUNC,
#if defined(FEAT_EVAL)
			    (char_u *)&p_imaf, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
# else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
# endif
			    SCTX_INIT},
options[158] = (struct vimoption) {"imactivatekey","imak",P_STRING|P_VI_DEF,
#if defined(FEAT_XIM) && defined(FEAT_GUI_GTK)
			    (char_u *)&p_imak, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[159] = (struct vimoption) {"imcmdline",   "imc",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_imcmdline, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[160] = (struct vimoption) {"imdisable",   "imd",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_imdisable, PV_NONE,
#ifdef __sgi
			    {(char_u *)TRUE, (char_u *)0L}
#else
			    {(char_u *)FALSE, (char_u *)0L}
#endif
			    SCTX_INIT},
options[161] = (struct vimoption) {"iminsert",    "imi",  P_NUM|P_VI_DEF,
			    (char_u *)&p_iminsert, PV_IMI,
			    {(char_u *)B_IMODE_NONE, (char_u *)0L}
			    SCTX_INIT},
options[162] = (struct vimoption) {"imsearch",    "ims",  P_NUM|P_VI_DEF,
			    (char_u *)&p_imsearch, PV_IMS,
			    {(char_u *)B_IMODE_USE_INSERT, (char_u *)0L}
			    SCTX_INIT},
options[163] = (struct vimoption) {"imstatusfunc","imsf",P_STRING|P_VI_DEF|P_SECURE,
#if defined(FEAT_EVAL)
			    (char_u *)&p_imsf, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[164] = (struct vimoption) {"imstyle",	    "imst", P_NUM|P_VI_DEF|P_SECURE,
#if defined(FEAT_XIM) && defined(FEAT_GUI_GTK)
			    (char_u *)&p_imst, PV_NONE,
			    {(char_u *)IM_OVER_THE_SPOT, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[165] = (struct vimoption) {"include",	    "inc",  P_STRING|P_ALLOCED|P_VI_DEF,
#ifdef FEAT_FIND_ID
			    (char_u *)&p_inc, PV_INC,
			    {(char_u *)"^\\s*#\\s*include", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[166] = (struct vimoption) {"includeexpr", "inex", P_STRING|P_ALLOCED|P_VI_DEF|P_MLE,
#if defined(FEAT_FIND_ID) && defined(FEAT_EVAL)
			    (char_u *)&p_inex, PV_INEX,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[167] = (struct vimoption) {"incsearch",   "is",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_is, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[168] = (struct vimoption) {"indentexpr", "inde",  P_STRING|P_ALLOCED|P_VI_DEF|P_VIM|P_MLE,
#if defined(FEAT_EVAL)
			    (char_u *)&p_inde, PV_INDE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[169] = (struct vimoption) {"indentkeys", "indk",  P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
#if defined(FEAT_EVAL)
			    (char_u *)&p_indk, PV_INDK,
			    {INDENTKEYS_DEFAULT, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[170] = (struct vimoption) {"infercase",   "inf",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_inf, PV_INF,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[171] = (struct vimoption) {"insertmode",  "im",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_im, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[172] = (struct vimoption) {"isfname",	    "isf",  P_STRING|P_VI_DEF|P_COMMA|P_NODUP,
			    (char_u *)&p_isf, PV_NONE,
			    {
#ifdef BACKSLASH_IN_FILENAME
				// Excluded are: & and ^ are special in cmd.exe
				// ( and ) are used in text separating fnames
			    (char_u *)"@,48-57,/,\\,.,-,_,+,,,#,$,%,{,},[,],:,@-@,!,~,=",
#else
# if defined(AMIGA)
			    (char_u *)"@,48-57,/,.,-,_,+,,,$,:",
# elif defined(VMS)
			    (char_u *)"@,48-57,/,.,-,_,+,,,#,$,%,<,>,[,],:,;,~",
# else // UNIX et al.
			    (char_u *)"@,48-57,/,.,-,_,+,,,#,$,%,~,=",
# endif
#endif
				(char_u *)0L} SCTX_INIT},
options[173] = (struct vimoption) {"isident",	    "isi",  P_STRING|P_VI_DEF|P_COMMA|P_NODUP,
			    (char_u *)&p_isi, PV_NONE,
			    {
#if defined(MSWIN)
			    (char_u *)"@,48-57,_,128-167,224-235",
#else
			    (char_u *)"@,48-57,_,192-255",
#endif
				(char_u *)0L} SCTX_INIT},
options[174] = (struct vimoption) {"iskeyword",   "isk",  P_STRING|P_ALLOCED|P_VIM|P_COMMA|P_NODUP,
			    (char_u *)&p_isk, PV_ISK,
			    {
				(char_u *)"@,48-57,_",
#if defined(MSWIN)
				(char_u *)"@,48-57,_,128-167,224-235"
#else
				ISK_LATIN1
#endif
			    } SCTX_INIT},
options[175] = (struct vimoption) {"isprint",	    "isp",  P_STRING|P_VI_DEF|P_RALL|P_COMMA|P_NODUP,
			    (char_u *)&p_isp, PV_NONE,
			    {
#if defined(MSWIN) || defined(VMS)
			    (char_u *)"@,~-255",
#else
			    ISP_LATIN1,
#endif
				(char_u *)0L} SCTX_INIT},
options[176] = (struct vimoption) {"joinspaces",  "js",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_js, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[177] = (struct vimoption) {"key",	    NULL,   P_STRING|P_ALLOCED|P_VI_DEF|P_NO_MKRC,
#ifdef FEAT_CRYPT
			    (char_u *)&p_key, PV_KEY,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[178] = (struct vimoption) {"keymap",	    "kmp",  P_STRING|P_ALLOCED|P_VI_DEF|P_RBUF|P_RSTAT|P_NFNAME|P_PRI_MKRC,
#ifdef FEAT_KEYMAP
			    (char_u *)&p_keymap, PV_KMAP,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#endif
			    SCTX_INIT},
options[179] = (struct vimoption) {"keymodel",    "km",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_km, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[180] = (struct vimoption) {"keywordprg",  "kp",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
			    (char_u *)&p_kp, PV_KP,
			    {
#if defined(MSWIN)
			    (char_u *)":help",
#elif defined(VMS)
			    (char_u *)"help",
#elif defined(USEMAN_S)
			    (char_u *)"man -s",
#else
			    (char_u *)"man",
#endif
				(char_u *)0L} SCTX_INIT},
options[181] = (struct vimoption) {"langmap",     "lmap", P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP|P_SECURE,
#ifdef FEAT_LANGMAP
			    (char_u *)&p_langmap, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[182] = (struct vimoption) {"langmenu",    "lm",   P_STRING|P_VI_DEF|P_NFNAME,
#if defined(FEAT_MENU) && defined(FEAT_MULTI_LANG)
			    (char_u *)&p_lm, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[183] = (struct vimoption) {"langnoremap",  "lnr",   P_BOOL|P_VI_DEF,
#ifdef FEAT_LANGMAP
			    (char_u *)&p_lnr, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[184] = (struct vimoption) {"langremap",  "lrm",   P_BOOL|P_VI_DEF,
#ifdef FEAT_LANGMAP
			    (char_u *)&p_lrm, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[185] = (struct vimoption) {"laststatus",  "ls",   P_NUM|P_VI_DEF|P_RALL,
			    (char_u *)&p_ls, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[186] = (struct vimoption) {"lazyredraw",  "lz",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_lz, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[187] = (struct vimoption) {"linebreak",   "lbr",  P_BOOL|P_VI_DEF|P_RWIN,
#ifdef FEAT_LINEBREAK
			    (char_u *)VAR_WIN, PV_LBR,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[188] = (struct vimoption) {"lines",	    NULL,   P_NUM|P_NODEFAULT|P_NO_MKRC|P_VI_DEF|P_RCLR,
			    (char_u *)&Rows, PV_NONE,
			    {
#if defined(MSWIN)
			    (char_u *)25L,
#else
			    (char_u *)24L,
#endif
					    (char_u *)0L} SCTX_INIT},
options[189] = (struct vimoption) {"linespace",   "lsp",  P_NUM|P_VI_DEF|P_RCLR,
#ifdef FEAT_GUI
			    (char_u *)&p_linespace, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
#ifdef FEAT_GUI_MSWIN
			    {(char_u *)1L, (char_u *)0L}
#else
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[190] = (struct vimoption) {"lisp",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_lisp, PV_LISP,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[191] = (struct vimoption) {"lispwords",   "lw",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_lispwords, PV_LW,
			    {(char_u *)LISPWORD_VALUE, (char_u *)0L} SCTX_INIT},
options[192] = (struct vimoption) {"list",	    NULL,   P_BOOL|P_VI_DEF|P_RWIN,
			    (char_u *)VAR_WIN, PV_LIST,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[193] = (struct vimoption) {"listchars",   "lcs",  P_STRING|P_VI_DEF|P_RALL|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_lcs, PV_LCS,
			    {(char_u *)"eol:$", (char_u *)0L} SCTX_INIT},
options[194] = (struct vimoption) {"loadplugins", "lpl",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_lpl, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[195] = (struct vimoption) {"luadll",      NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_LUA)
			    (char_u *)&p_luadll, PV_NONE,
			    {(char_u *)DYNAMIC_LUA_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#endif
			    SCTX_INIT},
options[196] = (struct vimoption) {"macatsui",    NULL,   P_BOOL|P_VI_DEF|P_RCLR,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[197] = (struct vimoption) {"magic",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_magic, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[198] = (struct vimoption) {"makeef",	    "mef",  P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_mef, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[199] = (struct vimoption) {"makeencoding","menc", P_STRING|P_VI_DEF,
			    (char_u *)&p_menc, PV_MENC,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[200] = (struct vimoption) {"makeprg",	    "mp",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_mp, PV_MP,
# ifdef VMS
			    {(char_u *)"MMS", (char_u *)0L}
# else
			    {(char_u *)"make", (char_u *)0L}
# endif
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[201] = (struct vimoption) {"matchpairs",  "mps",  P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_mps, PV_MPS,
			    {(char_u *)"(:),{:},[:]", (char_u *)0L}
			    SCTX_INIT},
options[202] = (struct vimoption) {"matchtime",   "mat",  P_NUM|P_VI_DEF,
			    (char_u *)&p_mat, PV_NONE,
			    {(char_u *)5L, (char_u *)0L} SCTX_INIT},
options[203] = (struct vimoption) {"maxcombine",  "mco",  P_NUM|P_VI_DEF|P_CURSWANT,
			    (char_u *)&p_mco, PV_NONE,
			    {(char_u *)2, (char_u *)0L} SCTX_INIT},
options[204] = (struct vimoption) {"maxfuncdepth", "mfd", P_NUM|P_VI_DEF,
#ifdef FEAT_EVAL
			    (char_u *)&p_mfd, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)100L, (char_u *)0L} SCTX_INIT},
options[205] = (struct vimoption) {"maxmapdepth", "mmd",  P_NUM|P_VI_DEF,
			    (char_u *)&p_mmd, PV_NONE,
			    {(char_u *)1000L, (char_u *)0L} SCTX_INIT},
options[206] = (struct vimoption) {"maxmem",	    "mm",   P_NUM|P_VI_DEF,
			    (char_u *)&p_mm, PV_NONE,
			    {(char_u *)DFLT_MAXMEM, (char_u *)0L}
			    SCTX_INIT},
options[207] = (struct vimoption) {"maxmempattern","mmp", P_NUM|P_VI_DEF,
			    (char_u *)&p_mmp, PV_NONE,
			    {(char_u *)1000L, (char_u *)0L} SCTX_INIT},
options[208] = (struct vimoption) {"maxmemtot",   "mmt",  P_NUM|P_VI_DEF,
			    (char_u *)&p_mmt, PV_NONE,
			    {(char_u *)DFLT_MAXMEMTOT, (char_u *)0L}
			    SCTX_INIT},
options[209] = (struct vimoption) {"menuitems",   "mis",  P_NUM|P_VI_DEF,
#ifdef FEAT_MENU
			    (char_u *)&p_mis, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)25L, (char_u *)0L} SCTX_INIT},
options[210] = (struct vimoption) {"mesg",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[211] = (struct vimoption) {"mkspellmem",  "msm",  P_STRING|P_VI_DEF|P_EXPAND|P_SECURE,
#ifdef FEAT_SPELL
			    (char_u *)&p_msm, PV_NONE,
			    {(char_u *)"460000,2000,500", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[212] = (struct vimoption) {"modeline",    "ml",   P_BOOL|P_VIM,
			    (char_u *)&p_ml, PV_ML,
			    {(char_u *)FALSE, (char_u *)TRUE} SCTX_INIT},
options[213] = (struct vimoption) {"modelineexpr", "mle",  P_BOOL|P_VI_DEF|P_SECURE,
			    (char_u *)&p_mle, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[214] = (struct vimoption) {"modelines",   "mls",  P_NUM|P_VI_DEF,
			    (char_u *)&p_mls, PV_NONE,
			    {(char_u *)5L, (char_u *)0L} SCTX_INIT},
options[215] = (struct vimoption) {"modifiable",  "ma",   P_BOOL|P_VI_DEF|P_NOGLOB,
			    (char_u *)&p_ma, PV_MA,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[216] = (struct vimoption) {"modified",    "mod",  P_BOOL|P_NO_MKRC|P_VI_DEF|P_RSTAT,
			    (char_u *)&p_mod, PV_MOD,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[217] = (struct vimoption) {"more",	    NULL,   P_BOOL|P_VIM,
			    (char_u *)&p_more, PV_NONE,
			    {(char_u *)FALSE, (char_u *)TRUE} SCTX_INIT},
options[218] = (struct vimoption) {"mouse",	    NULL,   P_STRING|P_VI_DEF|P_FLAGLIST,
			    (char_u *)&p_mouse, PV_NONE,
			    {
#if defined(MSWIN)
				(char_u *)"a",
#else
				(char_u *)"",
#endif
				(char_u *)0L} SCTX_INIT},
options[219] = (struct vimoption) {"mousefocus",   "mousef", P_BOOL|P_VI_DEF,
#ifdef FEAT_GUI
			    (char_u *)&p_mousef, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[220] = (struct vimoption) {"mousehide",   "mh",   P_BOOL|P_VI_DEF,
#ifdef FEAT_GUI
			    (char_u *)&p_mh, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[221] = (struct vimoption) {"mousemodel",  "mousem", P_STRING|P_VI_DEF,
			    (char_u *)&p_mousem, PV_NONE,
			    {
#if defined(MSWIN)
				(char_u *)"popup",
#else
# if defined(MACOS_X)
				(char_u *)"popup_setpos",
# else
				(char_u *)"extend",
# endif
#endif
				(char_u *)0L} SCTX_INIT},
options[222] = (struct vimoption) {"mousemoveevent",   "mousemev",   P_BOOL|P_VI_DEF,
#ifdef FEAT_GUI
			    (char_u *)&p_mousemev, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[223] = (struct vimoption) {"mouseshape",  "mouses",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_MOUSESHAPE
			    (char_u *)&p_mouseshape, PV_NONE,
			    {(char_u *)"i-r:beam,s:updown,sd:udsizing,vs:leftright,vd:lrsizing,m:no,ml:up-arrow,v:rightup-arrow", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[224] = (struct vimoption) {"mousetime",   "mouset",	P_NUM|P_VI_DEF,
			    (char_u *)&p_mouset, PV_NONE,
			    {(char_u *)500L, (char_u *)0L} SCTX_INIT},
options[225] = (struct vimoption) {"mzschemedll", NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_MZSCHEME)
			    (char_u *)&p_mzschemedll, PV_NONE,
			    {(char_u *)DYNAMIC_MZSCH_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#endif
			    SCTX_INIT},
options[226] = (struct vimoption) {"mzschemegcdll", NULL, P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_MZSCHEME)
			    (char_u *)&p_mzschemegcdll, PV_NONE,
			    {(char_u *)DYNAMIC_MZGC_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#endif
			    SCTX_INIT},
options[227] = (struct vimoption) {"mzquantum",  "mzq",   P_NUM,
#ifdef FEAT_MZSCHEME
			    (char_u *)&p_mzq, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)100L, (char_u *)100L} SCTX_INIT},
options[228] = (struct vimoption) {"novice",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[229] = (struct vimoption) {"nrformats",   "nf",   P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_nf, PV_NF,
			    {(char_u *)"bin,octal,hex", (char_u *)0L}
			    SCTX_INIT},
options[230] = (struct vimoption) {"number",	    "nu",   P_BOOL|P_VI_DEF|P_RWIN,
			    (char_u *)VAR_WIN, PV_NU,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[231] = (struct vimoption) {"numberwidth", "nuw",  P_NUM|P_RWIN|P_VIM,
#ifdef FEAT_LINEBREAK
			    (char_u *)VAR_WIN, PV_NUW,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)8L, (char_u *)4L} SCTX_INIT},
options[232] = (struct vimoption) {"omnifunc",    "ofu",  P_STRING|P_ALLOCED|P_VI_DEF|P_SECURE,
#ifdef FEAT_COMPL_FUNC
			    (char_u *)&p_ofu, PV_OFU,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[233] = (struct vimoption) {"open",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[234] = (struct vimoption) {"opendevice",  "odev", P_BOOL|P_VI_DEF,
#if defined(MSWIN)
			    (char_u *)&p_odev, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)FALSE}
			    SCTX_INIT},
options[235] = (struct vimoption) {"operatorfunc", "opfunc", P_STRING|P_VI_DEF|P_SECURE,
			    (char_u *)&p_opfunc, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[236] = (struct vimoption) {"optimize",    "opt",  P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[237] = (struct vimoption) {"osfiletype",  "oft",  P_STRING|P_ALLOCED|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[238] = (struct vimoption) {"packpath",    "pp",   P_STRING|P_VI_DEF|P_EXPAND|P_ONECOMMA|P_NODUP
								    |P_SECURE,
			    (char_u *)&p_pp, PV_NONE,
			    {(char_u *)DFLT_RUNTIMEPATH, (char_u *)0L}
			    SCTX_INIT},
options[239] = (struct vimoption) {"paragraphs",  "para", P_STRING|P_VI_DEF,
			    (char_u *)&p_para, PV_NONE,
			    {(char_u *)"IPLPPPQPP TPHPLIPpLpItpplpipbp",
				(char_u *)0L} SCTX_INIT},
options[240] = (struct vimoption) {"paste",	    NULL,   P_BOOL|P_VI_DEF|P_PRI_MKRC,
			    (char_u *)&p_paste, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[241] = (struct vimoption) {"pastetoggle", "pt",   P_STRING|P_VI_DEF,
			    (char_u *)&p_pt, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[242] = (struct vimoption) {"patchexpr",   "pex",  P_STRING|P_VI_DEF|P_SECURE,
#if defined(FEAT_DIFF) && defined(FEAT_EVAL)
			    (char_u *)&p_pex, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[243] = (struct vimoption) {"patchmode",   "pm",   P_STRING|P_VI_DEF|P_NFNAME,
			    (char_u *)&p_pm, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[244] = (struct vimoption) {"path",	    "pa",   P_STRING|P_EXPAND|P_VI_DEF|P_COMMA|P_NODUP,
			    (char_u *)&p_path, PV_PATH,
			    {
#if defined(AMIGA) || defined(MSWIN)
			    (char_u *)".,,",
#else
			    (char_u *)".,/usr/include,,",
#endif
				(char_u *)0L} SCTX_INIT},
options[245] = (struct vimoption) {"perldll",     NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_PERL)
			    (char_u *)&p_perldll, PV_NONE,
			    {(char_u *)DYNAMIC_PERL_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[246] = (struct vimoption) {"preserveindent", "pi", P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_pi, PV_PI,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[247] = (struct vimoption) {"previewheight", "pvh", P_NUM|P_VI_DEF,
#if defined(FEAT_QUICKFIX)
			    (char_u *)&p_pvh, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)12L, (char_u *)0L} SCTX_INIT},
options[248] = (struct vimoption) {"previewpopup", "pvp", P_STRING|P_VI_DEF|P_COMMA|P_NODUP,
#ifdef FEAT_PROP_POPUP
			    (char_u *)&p_pvp, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[249] = (struct vimoption) {"previewwindow", "pvw", P_BOOL|P_VI_DEF|P_RSTAT|P_NOGLOB,
#if defined(FEAT_QUICKFIX)
			    (char_u *)VAR_WIN, PV_PVW,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[250] = (struct vimoption) {"printdevice", "pdev", P_STRING|P_VI_DEF|P_SECURE,
#ifdef FEAT_PRINTER
			    (char_u *)&p_pdev, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[251] = (struct vimoption) {"printencoding", "penc", P_STRING|P_VI_DEF,
#ifdef FEAT_POSTSCRIPT
			    (char_u *)&p_penc, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[252] = (struct vimoption) {"printexpr", "pexpr",  P_STRING|P_VI_DEF|P_SECURE,
#ifdef FEAT_POSTSCRIPT
			    (char_u *)&p_pexpr, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[253] = (struct vimoption) {"printfont", "pfn",    P_STRING|P_VI_DEF,
#ifdef FEAT_PRINTER
			    (char_u *)&p_pfn, PV_NONE,
			    {
# ifdef MSWIN
				(char_u *)"Courier_New:h10",
# else
				(char_u *)"courier",
# endif
				(char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[254] = (struct vimoption) {"printheader", "pheader",  P_STRING|P_VI_DEF|P_GETTEXT,
#ifdef FEAT_PRINTER
			    (char_u *)&p_header, PV_NONE,
			    // untranslated to avoid problems when 'encoding'
			    // is changed
			    {(char_u *)"%<%f%h%m%=Page %N", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[255] = (struct vimoption) {"printmbcharset", "pmbcs",  P_STRING|P_VI_DEF,
#if defined(FEAT_POSTSCRIPT)
			    (char_u *)&p_pmcs, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[256] = (struct vimoption) {"printmbfont", "pmbfn",  P_STRING|P_VI_DEF,
#if defined(FEAT_POSTSCRIPT)
			    (char_u *)&p_pmfn, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[257] = (struct vimoption) {"printoptions", "popt", P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_PRINTER
			    (char_u *)&p_popt, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[258] = (struct vimoption) {"prompt",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_prompt, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[259] = (struct vimoption) {"pumheight",   "ph",   P_NUM|P_VI_DEF,
			    (char_u *)&p_ph, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[260] = (struct vimoption) {"pumwidth",    "pw",   P_NUM|P_VI_DEF,
			    (char_u *)&p_pw, PV_NONE,
			    {(char_u *)15L, (char_u *)15L} SCTX_INIT},
options[261] = (struct vimoption) {"pythonthreedll",  NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_PYTHON3)
			    (char_u *)&p_py3dll, PV_NONE,
			    {(char_u *)DYNAMIC_PYTHON3_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[262] = (struct vimoption) {"pythonthreehome", NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(FEAT_PYTHON3)
			    (char_u *)&p_py3home, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[263] = (struct vimoption) {"pythondll",   NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_PYTHON)
			    (char_u *)&p_pydll, PV_NONE,
			    {(char_u *)DYNAMIC_PYTHON_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[264] = (struct vimoption) {"pythonhome",  NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(FEAT_PYTHON)
			    (char_u *)&p_pyhome, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[265] = (struct vimoption) {"pyxversion", "pyx",   P_NUM|P_VI_DEF|P_SECURE,
#if defined(FEAT_PYTHON) || defined(FEAT_PYTHON3)
			    (char_u *)&p_pyx, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)DEFAULT_PYTHON_VER, (char_u *)0L}
			    SCTX_INIT},
options[266] = (struct vimoption) {"quickfixtextfunc", "qftf", P_STRING|P_ALLOCED|P_VI_DEF|P_VIM|P_SECURE|P_FUNC,
#if defined(FEAT_QUICKFIX) && defined(FEAT_EVAL)
			    (char_u *)&p_qftf, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)NULL}
#endif
			    SCTX_INIT},
options[267] = (struct vimoption) {"quoteescape", "qe",   P_STRING|P_ALLOCED|P_VI_DEF,
#ifdef FEAT_PROP_POPUP
			    (char_u *)&p_qe, PV_QE,
			    {(char_u *)"\\", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[268] = (struct vimoption) {"readonly",    "ro",   P_BOOL|P_VI_DEF|P_RSTAT|P_NOGLOB,
			    (char_u *)&p_ro, PV_RO,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[269] = (struct vimoption) {"redraw",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[270] = (struct vimoption) {"redrawtime",  "rdt",  P_NUM|P_VI_DEF,
#ifdef FEAT_RELTIME
			    (char_u *)&p_rdt, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)2000L, (char_u *)0L} SCTX_INIT},
options[271] = (struct vimoption) {"regexpengine", "re",  P_NUM|P_VI_DEF,
			    (char_u *)&p_re, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[272] = (struct vimoption) {"relativenumber", "rnu", P_BOOL|P_VI_DEF|P_RWIN,
			    (char_u *)VAR_WIN, PV_RNU,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[273] = (struct vimoption) {"remap",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_remap, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[274] = (struct vimoption) {"renderoptions", "rop", P_STRING|P_ONECOMMA|P_RCLR|P_VI_DEF,
#ifdef FEAT_RENDER_OPTIONS
			    (char_u *)&p_rop, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[275] = (struct vimoption) {"report",	    NULL,   P_NUM|P_VI_DEF,
			    (char_u *)&p_report, PV_NONE,
			    {(char_u *)2L, (char_u *)0L} SCTX_INIT},
options[276] = (struct vimoption) {"restorescreen", "rs", P_BOOL|P_VI_DEF,
#ifdef MSWIN
			    (char_u *)&p_rs, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[277] = (struct vimoption) {"revins",	    "ri",   P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)&p_ri, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[278] = (struct vimoption) {"rightleft",   "rl",   P_BOOL|P_VI_DEF|P_RWIN,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)VAR_WIN, PV_RL,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[279] = (struct vimoption) {"rightleftcmd", "rlc", P_STRING|P_ALLOCED|P_VI_DEF|P_RWIN,
#ifdef FEAT_RIGHTLEFT
			    (char_u *)VAR_WIN, PV_RLC,
			    {(char_u *)"search", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[280] = (struct vimoption) {"rubydll",     NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_RUBY)
			    (char_u *)&p_rubydll, PV_NONE,
			    {(char_u *)DYNAMIC_RUBY_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[281] = (struct vimoption) {"ruler",	    "ru",   P_BOOL|P_VI_DEF|P_VIM|P_RSTAT,
#ifdef FEAT_CMDL_INFO
			    (char_u *)&p_ru, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[282] = (struct vimoption) {"rulerformat", "ruf",  P_STRING|P_VI_DEF|P_ALLOCED|P_RSTAT|P_MLE,
#ifdef FEAT_STL_OPT
			    (char_u *)&p_ruf, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[283] = (struct vimoption) {"runtimepath", "rtp",  P_STRING|P_VI_DEF|P_EXPAND|P_ONECOMMA|P_NODUP
								    |P_SECURE,
			    (char_u *)&p_rtp, PV_NONE,
			    {(char_u *)DFLT_RUNTIMEPATH, (char_u *)0L}
			    SCTX_INIT},
options[284] = (struct vimoption) {"scroll",	    "scr",  P_NUM|P_NO_MKRC|P_VI_DEF,
			    (char_u *)VAR_WIN, PV_SCROLL,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[285] = (struct vimoption) {"scrollbind",  "scb",  P_BOOL|P_VI_DEF,
			    (char_u *)VAR_WIN, PV_SCBIND,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[286] = (struct vimoption) {"scrollfocus", "scf",  P_BOOL|P_VI_DEF,
#if defined(MSWIN) && defined(FEAT_GUI)
			    (char_u *)&p_scf, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[287] = (struct vimoption) {"scrolljump",  "sj",   P_NUM|P_VI_DEF|P_VIM,
			    (char_u *)&p_sj, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[288] = (struct vimoption) {"scrolloff",   "so",   P_NUM|P_VI_DEF|P_VIM|P_RALL,
			    (char_u *)&p_so, PV_SO,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[289] = (struct vimoption) {"scrollopt",   "sbo",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_sbo, PV_NONE,
			    {(char_u *)"ver,jump", (char_u *)0L}
			    SCTX_INIT},
options[290] = (struct vimoption) {"sections",    "sect", P_STRING|P_VI_DEF,
			    (char_u *)&p_sections, PV_NONE,
			    {(char_u *)"SHNHH HUnhsh", (char_u *)0L}
			    SCTX_INIT},
options[291] = (struct vimoption) {"secure",	    NULL,   P_BOOL|P_VI_DEF|P_SECURE,
			    (char_u *)&p_secure, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[292] = (struct vimoption) {"selection",   "sel",  P_STRING|P_VI_DEF,
			    (char_u *)&p_sel, PV_NONE,
			    {(char_u *)"inclusive", (char_u *)0L}
			    SCTX_INIT},
options[293] = (struct vimoption) {"selectmode",  "slm",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_slm, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[294] = (struct vimoption) {"sessionoptions", "ssop", P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_SESSION
			    (char_u *)&p_ssop, PV_NONE,
	 {(char_u *)"blank,buffers,curdir,folds,help,options,tabpages,winsize,terminal",
							       (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[295] = (struct vimoption) {"shell",	    "sh",   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
			    (char_u *)&p_sh, PV_NONE,
			    {
#ifdef VMS
			    (char_u *)"-",
#else
# if defined(MSWIN)
			    (char_u *)"",	// set in set_init_1()
# else
			    (char_u *)"sh",
# endif
#endif // VMS
				(char_u *)0L} SCTX_INIT},
options[296] = (struct vimoption) {"shellcmdflag","shcf", P_STRING|P_VI_DEF|P_SECURE,
			    (char_u *)&p_shcf, PV_NONE,
			    {
#if defined(MSWIN)
			    (char_u *)"/c",
#else
			    (char_u *)"-c",
#endif
				(char_u *)0L} SCTX_INIT},
options[297] = (struct vimoption) {"shellpipe",   "sp",   P_STRING|P_VI_DEF|P_SECURE,
#ifdef FEAT_QUICKFIX
			    (char_u *)&p_sp, PV_NONE,
			    {
#if defined(UNIX)
			    (char_u *)"| tee",
#else
			    (char_u *)">",
#endif
				(char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[298] = (struct vimoption) {"shellquote",  "shq",  P_STRING|P_VI_DEF|P_SECURE,
			    (char_u *)&p_shq, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[299] = (struct vimoption) {"shellredir",  "srr",  P_STRING|P_VI_DEF|P_SECURE,
			    (char_u *)&p_srr, PV_NONE,
			    {(char_u *)">", (char_u *)0L} SCTX_INIT},
options[300] = (struct vimoption) {"shellslash",  "ssl",   P_BOOL|P_VI_DEF,
#ifdef BACKSLASH_IN_FILENAME
			    (char_u *)&p_ssl, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[301] = (struct vimoption) {"shelltemp",   "stmp", P_BOOL,
			    (char_u *)&p_stmp, PV_NONE,
			    {(char_u *)FALSE, (char_u *)TRUE} SCTX_INIT},
options[302] = (struct vimoption) {"shelltype",   "st",   P_NUM|P_VI_DEF,
#ifdef AMIGA
			    (char_u *)&p_st, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[303] = (struct vimoption) {"shellxquote", "sxq",  P_STRING|P_VI_DEF|P_SECURE,
			    (char_u *)&p_sxq, PV_NONE,
			    {
#if defined(UNIX) && defined(USE_SYSTEM)
			    (char_u *)"\"",
#else
			    (char_u *)"",
#endif
				(char_u *)0L} SCTX_INIT},
options[304] = (struct vimoption) {"shellxescape", "sxe", P_STRING|P_VI_DEF|P_SECURE,
			    (char_u *)&p_sxe, PV_NONE,
			    {
#if defined(MSWIN)
			    (char_u *)"\"&|<>()@^",
#else
			    (char_u *)"",
#endif
				(char_u *)0L} SCTX_INIT},
options[305] = (struct vimoption) {"shiftround",  "sr",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_sr, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[306] = (struct vimoption) {"shiftwidth",  "sw",   P_NUM|P_VI_DEF,
			    (char_u *)&p_sw, PV_SW,
			    {(char_u *)8L, (char_u *)0L} SCTX_INIT},
options[307] = (struct vimoption) {"shortmess",   "shm",  P_STRING|P_VIM|P_FLAGLIST,
			    (char_u *)&p_shm, PV_NONE,
			    {(char_u *)"S", (char_u *)"filnxtToOS"}
			    SCTX_INIT},
options[308] = (struct vimoption) {"shortname",   "sn",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_sn, PV_SN,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[309] = (struct vimoption) {"showbreak",   "sbr",  P_STRING|P_VI_DEF|P_RALL,
#ifdef FEAT_LINEBREAK
			    (char_u *)&p_sbr, PV_SBR,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[310] = (struct vimoption) {"showcmd",	    "sc",   P_BOOL|P_VIM,
#ifdef FEAT_CMDL_INFO
			    (char_u *)&p_sc, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE,
#ifdef UNIX
				(char_u *)FALSE
#else
				(char_u *)TRUE
#endif
				} SCTX_INIT},
options[311] = (struct vimoption) {"showfulltag", "sft",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_sft, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[312] = (struct vimoption) {"showmatch",   "sm",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_sm, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[313] = (struct vimoption) {"showmode",    "smd",  P_BOOL|P_VIM,
			    (char_u *)&p_smd, PV_NONE,
			    {(char_u *)FALSE, (char_u *)TRUE} SCTX_INIT},
options[314] = (struct vimoption) {"showtabline", "stal", P_NUM|P_VI_DEF|P_RALL,
			    (char_u *)&p_stal, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[315] = (struct vimoption) {"sidescroll",  "ss",   P_NUM|P_VI_DEF,
			    (char_u *)&p_ss, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[316] = (struct vimoption) {"sidescrolloff", "siso", P_NUM|P_VI_DEF|P_VIM|P_RBUF,
			    (char_u *)&p_siso, PV_SISO,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[317] = (struct vimoption) {"signcolumn",   "scl",  P_STRING|P_ALLOCED|P_VI_DEF|P_RCLR,
#ifdef FEAT_SIGNS
			    (char_u *)VAR_WIN, PV_SCL,
			    {(char_u *)"auto", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[318] = (struct vimoption) {"slowopen",    "slow", P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[319] = (struct vimoption) {"smartcase",   "scs",  P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_scs, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[320] = (struct vimoption) {"smartindent", "si",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_si, PV_SI,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[321] = (struct vimoption) {"smarttab",    "sta",  P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_sta, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[322] = (struct vimoption) {"softtabstop", "sts",  P_NUM|P_VI_DEF|P_VIM,
			    (char_u *)&p_sts, PV_STS,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[323] = (struct vimoption) {"sourceany",   NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[324] = (struct vimoption) {"spell",	    NULL,   P_BOOL|P_VI_DEF|P_RWIN,
#ifdef FEAT_SPELL
			    (char_u *)VAR_WIN, PV_SPELL,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[325] = (struct vimoption) {"spellcapcheck", "spc", P_STRING|P_ALLOCED|P_VI_DEF|P_RBUF,
#ifdef FEAT_SPELL
			    (char_u *)&p_spc, PV_SPC,
			    {(char_u *)"[.?!]\\_[\\])'\"	 ]\\+", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[326] = (struct vimoption) {"spellfile",   "spf",  P_STRING|P_EXPAND|P_ALLOCED|P_VI_DEF|P_SECURE
								  |P_ONECOMMA,
#ifdef FEAT_SPELL
			    (char_u *)&p_spf, PV_SPF,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[327] = (struct vimoption) {"spelllang",   "spl",  P_STRING|P_ALLOCED|P_VI_DEF|P_ONECOMMA
							     |P_RBUF|P_EXPAND,
#ifdef FEAT_SPELL
			    (char_u *)&p_spl, PV_SPL,
			    {(char_u *)"en", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[328] = (struct vimoption) {"spelloptions", "spo",  P_STRING|P_ALLOCED|P_VI_DEF
						    |P_ONECOMMA|P_NODUP|P_RBUF,
#ifdef FEAT_SPELL
			    (char_u *)&p_spo, PV_SPO,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[329] = (struct vimoption) {"spellsuggest", "sps", P_STRING|P_VI_DEF|P_EXPAND|P_SECURE|P_ONECOMMA,
#ifdef FEAT_SPELL
			    (char_u *)&p_sps, PV_NONE,
			    {(char_u *)"best", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[330] = (struct vimoption) {"splitbelow",  "sb",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_sb, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[331] = (struct vimoption) {"splitright",  "spr",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_spr, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[332] = (struct vimoption) {"startofline", "sol",  P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_sol, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[333] = (struct vimoption) {"statusline"  ,"stl",  P_STRING|P_VI_DEF|P_ALLOCED|P_RSTAT|P_MLE,
#ifdef FEAT_STL_OPT
			    (char_u *)&p_stl, PV_STL,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[334] = (struct vimoption) {"suffixes",    "su",   P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_su, PV_NONE,
			    {(char_u *)".bak,~,.o,.h,.info,.swp,.obj",
				(char_u *)0L} SCTX_INIT},
options[335] = (struct vimoption) {"suffixesadd", "sua",  P_STRING|P_VI_DEF|P_ALLOCED|P_ONECOMMA|P_NODUP,
#ifdef FEAT_SEARCHPATH
			    (char_u *)&p_sua, PV_SUA,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[336] = (struct vimoption) {"swapfile",    "swf",  P_BOOL|P_VI_DEF|P_RSTAT,
			    (char_u *)&p_swf, PV_SWF,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[337] = (struct vimoption) {"swapsync",    "sws",  P_STRING|P_VI_DEF,
			    (char_u *)&p_sws, PV_NONE,
			    {(char_u *)"fsync", (char_u *)0L} SCTX_INIT},
options[338] = (struct vimoption) {"switchbuf",   "swb",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_swb, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[339] = (struct vimoption) {"synmaxcol",   "smc",  P_NUM|P_VI_DEF|P_RBUF,
#ifdef FEAT_SYN_HL
			    (char_u *)&p_smc, PV_SMC,
			    {(char_u *)3000L, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[340] = (struct vimoption) {"syntax",	    "syn",  P_STRING|P_ALLOCED|P_VI_DEF|P_NOGLOB|P_NFNAME,
#ifdef FEAT_SYN_HL
			    (char_u *)&p_syn, PV_SYN,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[341] = (struct vimoption) {"tabline",	    "tal",  P_STRING|P_VI_DEF|P_RALL|P_MLE,
#ifdef FEAT_STL_OPT
			    (char_u *)&p_tal, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[342] = (struct vimoption) {"tabpagemax",  "tpm",  P_NUM|P_VI_DEF,
			    (char_u *)&p_tpm, PV_NONE,
			    {(char_u *)10L, (char_u *)0L} SCTX_INIT},
options[343] = (struct vimoption) {"tabstop",	    "ts",   P_NUM|P_VI_DEF|P_RBUF,
			    (char_u *)&p_ts, PV_TS,
			    {(char_u *)8L, (char_u *)0L} SCTX_INIT},
options[344] = (struct vimoption) {"tagbsearch",  "tbs",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_tbs, PV_NONE,
#ifdef VMS	// binary searching doesn't appear to work on VMS
			    {(char_u *)0L, (char_u *)0L}
#else
			    {(char_u *)TRUE, (char_u *)0L}
#endif
			    SCTX_INIT},
options[345] = (struct vimoption) {"tagcase",	    "tc",   P_STRING|P_VIM,
			    (char_u *)&p_tc, PV_TC,
			    {(char_u *)"followic", (char_u *)"followic"} SCTX_INIT},
options[346] = (struct vimoption) {"tagfunc",    "tfu",   P_STRING|P_ALLOCED|P_VI_DEF|P_SECURE|P_FUNC,
#ifdef FEAT_EVAL
			    (char_u *)&p_tfu, PV_TFU,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[347] = (struct vimoption) {"taglength",   "tl",   P_NUM|P_VI_DEF,
			    (char_u *)&p_tl, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[348] = (struct vimoption) {"tagrelative", "tr",   P_BOOL|P_VIM,
			    (char_u *)&p_tr, PV_NONE,
			    {(char_u *)FALSE, (char_u *)TRUE} SCTX_INIT},
options[349] = (struct vimoption) {"tags",	    "tag",  P_STRING|P_EXPAND|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_tags, PV_TAGS,
			    {
#if defined(FEAT_EMACS_TAGS) && !defined(CASE_INSENSITIVE_FILENAME)
			    (char_u *)"./tags,./TAGS,tags,TAGS",
#else
			    (char_u *)"./tags,tags",
#endif
				(char_u *)0L} SCTX_INIT},
options[350] = (struct vimoption) {"tagstack",    "tgst", P_BOOL|P_VI_DEF,
			    (char_u *)&p_tgst, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[351] = (struct vimoption) {"tcldll",      NULL,   P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(DYNAMIC_TCL)
			    (char_u *)&p_tcldll, PV_NONE,
			    {(char_u *)DYNAMIC_TCL_DLL, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[352] = (struct vimoption) {"term",	    NULL,   P_STRING|P_EXPAND|P_NODEFAULT|P_NO_MKRC|P_VI_DEF|P_RALL,
			    (char_u *)&T_NAME, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[353] = (struct vimoption) {"termbidi", "tbidi",   P_BOOL|P_VI_DEF,
#ifdef FEAT_ARABIC
			    (char_u *)&p_tbidi, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[354] = (struct vimoption) {"termencoding", "tenc", P_STRING|P_VI_DEF|P_RCLR,
			    (char_u *)&p_tenc, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[355] = (struct vimoption) {"termguicolors", "tgc", P_BOOL|P_VI_DEF|P_VIM|P_RCLR,
#ifdef FEAT_TERMGUICOLORS
			    (char_u *)&p_tgc, PV_NONE,
			    {(char_u *)FALSE, (char_u *)FALSE}
#else
			    (char_u*)NULL, PV_NONE,
			    {(char_u *)FALSE, (char_u *)FALSE}
#endif
			    SCTX_INIT},
options[356] = (struct vimoption) {"termwinkey", "twk",   P_STRING|P_ALLOCED|P_RWIN|P_VI_DEF,
#ifdef FEAT_TERMINAL
			    (char_u *)VAR_WIN, PV_TWK,
			    {(char_u *)"", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[357] = (struct vimoption) {"termwinscroll", "twsl", P_NUM|P_VI_DEF|P_VIM|P_RBUF,
#ifdef FEAT_TERMINAL
			    (char_u *)&p_twsl, PV_TWSL,
			    {(char_u *)10000L, (char_u *)10000L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[358] = (struct vimoption) {"termwinsize", "tws",  P_STRING|P_ALLOCED|P_RWIN|P_VI_DEF,
#ifdef FEAT_TERMINAL
			    (char_u *)VAR_WIN, PV_TWS,
			    {(char_u *)"", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[359] = (struct vimoption) {"termwintype", "twt",  P_STRING|P_ALLOCED|P_VI_DEF,
#if defined(MSWIN) && defined(FEAT_TERMINAL)
			    (char_u *)&p_twt, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[360] = (struct vimoption) {"terse",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_terse, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[361] = (struct vimoption) {"textauto",    "ta",   P_BOOL|P_VIM,
			    (char_u *)&p_ta, PV_NONE,
			    {(char_u *)DFLT_TEXTAUTO, (char_u *)TRUE}
			    SCTX_INIT},
options[362] = (struct vimoption) {"textmode",    "tx",   P_BOOL|P_VI_DEF|P_NO_MKRC,
			    (char_u *)&p_tx, PV_TX,
			    {
#ifdef USE_CRNL
			    (char_u *)TRUE,
#else
			    (char_u *)FALSE,
#endif
				(char_u *)0L} SCTX_INIT},
options[363] = (struct vimoption) {"textwidth",   "tw",   P_NUM|P_VI_DEF|P_VIM|P_RBUF,
			    (char_u *)&p_tw, PV_TW,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[364] = (struct vimoption) {"thesaurus",   "tsr",  P_STRING|P_EXPAND|P_VI_DEF|P_ONECOMMA|P_NODUP|P_NDNAME,
			    (char_u *)&p_tsr, PV_TSR,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[365] = (struct vimoption) {"thesaurusfunc", "tsrfu",  P_STRING|P_ALLOCED|P_VI_DEF|P_SECURE|P_FUNC,
#ifdef FEAT_COMPL_FUNC
			    (char_u *)&p_tsrfu, PV_TSRFU,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[366] = (struct vimoption) {"tildeop",	    "top",  P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_to, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[367] = (struct vimoption) {"timeout",	    "to",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_timeout, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[368] = (struct vimoption) {"timeoutlen",  "tm",   P_NUM|P_VI_DEF,
			    (char_u *)&p_tm, PV_NONE,
			    {(char_u *)1000L, (char_u *)0L} SCTX_INIT},
options[369] = (struct vimoption) {"title",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_title, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[370] = (struct vimoption) {"titlelen",    NULL,   P_NUM|P_VI_DEF,
			    (char_u *)&p_titlelen, PV_NONE,
			    {(char_u *)85L, (char_u *)0L} SCTX_INIT},
options[371] = (struct vimoption) {"titleold",    NULL,   P_STRING|P_VI_DEF|P_GETTEXT|P_SECURE|P_NO_MKRC,
			    (char_u *)&p_titleold, PV_NONE,
			    {(char_u *)N_("Thanks for flying Vim"),
							       (char_u *)0L}
			    SCTX_INIT},
options[372] = (struct vimoption) {"titlestring", NULL,   P_STRING|P_VI_DEF|P_MLE,
			    (char_u *)&p_titlestring, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[373] = (struct vimoption) {"toolbar",     "tb",   P_STRING|P_ONECOMMA|P_VI_DEF|P_NODUP,
#if defined(FEAT_TOOLBAR) && !defined(FEAT_GUI_MSWIN)
			    (char_u *)&p_toolbar, PV_NONE,
			    {(char_u *)"icons,tooltips", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[374] = (struct vimoption) {"toolbariconsize",	"tbis", P_STRING|P_VI_DEF,
#if defined(FEAT_TOOLBAR) && defined(FEAT_GUI_GTK)
			    (char_u *)&p_tbis, PV_NONE,
			    {(char_u *)"small", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[375] = (struct vimoption) {"ttimeout",    NULL,   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_ttimeout, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[376] = (struct vimoption) {"ttimeoutlen", "ttm",  P_NUM|P_VI_DEF,
			    (char_u *)&p_ttm, PV_NONE,
			    {(char_u *)-1L, (char_u *)0L} SCTX_INIT},
options[377] = (struct vimoption) {"ttybuiltin",  "tbi",  P_BOOL|P_VI_DEF,
			    (char_u *)&p_tbi, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[378] = (struct vimoption) {"ttyfast",	    "tf",   P_BOOL|P_NO_MKRC|P_VI_DEF,
			    (char_u *)&p_tf, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[379] = (struct vimoption) {"ttymouse",    "ttym", P_STRING|P_NODEFAULT|P_NO_MKRC|P_VI_DEF,
#if defined(UNIX) || defined(VMS)
			    (char_u *)&p_ttym, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[380] = (struct vimoption) {"ttyscroll",   "tsl",  P_NUM|P_VI_DEF,
			    (char_u *)&p_ttyscroll, PV_NONE,
			    {(char_u *)999L, (char_u *)0L} SCTX_INIT},
options[381] = (struct vimoption) {"ttytype",	    "tty",  P_STRING|P_EXPAND|P_NODEFAULT|P_NO_MKRC|P_VI_DEF|P_RALL,
			    (char_u *)&T_NAME, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[382] = (struct vimoption) {"undodir",     "udir", P_STRING|P_EXPAND|P_ONECOMMA|P_NODUP|P_SECURE
								    |P_VI_DEF,
#ifdef FEAT_PERSISTENT_UNDO
			    (char_u *)&p_udir, PV_NONE,
			    {(char_u *)".", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[383] = (struct vimoption) {"undofile",    "udf",  P_BOOL|P_VI_DEF|P_VIM,
#ifdef FEAT_PERSISTENT_UNDO
			    (char_u *)&p_udf, PV_UDF,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[384] = (struct vimoption) {"undolevels",  "ul",   P_NUM|P_VI_DEF,
			    (char_u *)&p_ul, PV_UL,
			    {
#if defined(UNIX) || defined(MSWIN) || defined(VMS)
			    (char_u *)1000L,
#else
			    (char_u *)100L,
#endif
				(char_u *)0L} SCTX_INIT},
options[385] = (struct vimoption) {"undoreload",  "ur",   P_NUM|P_VI_DEF,
			    (char_u *)&p_ur, PV_NONE,
			    { (char_u *)10000L, (char_u *)0L} SCTX_INIT},
options[386] = (struct vimoption) {"updatecount", "uc",   P_NUM|P_VI_DEF,
			    (char_u *)&p_uc, PV_NONE,
			    {(char_u *)200L, (char_u *)0L} SCTX_INIT},
options[387] = (struct vimoption) {"updatetime",  "ut",   P_NUM|P_VI_DEF,
			    (char_u *)&p_ut, PV_NONE,
			    {(char_u *)4000L, (char_u *)0L} SCTX_INIT},
options[388] = (struct vimoption) {"varsofttabstop", "vsts",  P_STRING|P_VI_DEF|P_VIM|P_COMMA,
#ifdef FEAT_VARTABS
			    (char_u *)&p_vsts, PV_VSTS,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
#endif
			    SCTX_INIT},
options[389] = (struct vimoption) {"vartabstop",  "vts",  P_STRING|P_VI_DEF|P_VIM|P_RBUF|P_COMMA,
#ifdef FEAT_VARTABS
			    (char_u *)&p_vts, PV_VTS,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)"", (char_u *)NULL}
#endif
			    SCTX_INIT},
options[390] = (struct vimoption) {"verbose",	    "vbs",  P_NUM|P_VI_DEF,
			    (char_u *)&p_verbose, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[391] = (struct vimoption) {"verbosefile", "vfile", P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
			    (char_u *)&p_vfile, PV_NONE,
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[392] = (struct vimoption) {"viewdir",     "vdir", P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#ifdef FEAT_SESSION
			    (char_u *)&p_vdir, PV_NONE,
			    {(char_u *)DFLT_VDIR, (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[393] = (struct vimoption) {"viewoptions", "vop",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_SESSION
			    (char_u *)&p_vop, PV_NONE,
			    {(char_u *)"folds,options,cursor,curdir",
								  (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[394] = (struct vimoption) {"viminfo",	    "vi",   P_STRING|P_ONECOMMA|P_NODUP|P_SECURE,
#ifdef FEAT_VIMINFO
			    (char_u *)&p_viminfo, PV_NONE,
#if defined(MSWIN)
			    {(char_u *)"", (char_u *)"'100,<50,s10,h,rA:,rB:"}
#elif defined(AMIGA)
			    {(char_u *)"",
				 (char_u *)"'100,<50,s10,h,rdf0:,rdf1:,rdf2:"}
#else
			    {(char_u *)"", (char_u *)"'100,<50,s10,h"}
#endif
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[395] = (struct vimoption) {"viminfofile", "vif",  P_STRING|P_EXPAND|P_ONECOMMA|P_NODUP
							    |P_SECURE|P_VI_DEF,
#ifdef FEAT_VIMINFO
			    (char_u *)&p_viminfofile, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[396] = (struct vimoption) {"virtualedit", "ve",   P_STRING|P_ONECOMMA|P_NODUP|P_VI_DEF
							    |P_VIM|P_CURSWANT,
			    (char_u *)&p_ve, PV_VE,
			    {(char_u *)"", (char_u *)""}
			    SCTX_INIT},
options[397] = (struct vimoption) {"visualbell",  "vb",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_vb, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[398] = (struct vimoption) {"w300",	    NULL,   P_NUM|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[399] = (struct vimoption) {"w1200",	    NULL,   P_NUM|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[400] = (struct vimoption) {"w9600",	    NULL,   P_NUM|P_VI_DEF,
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[401] = (struct vimoption) {"warn",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_warn, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[402] = (struct vimoption) {"weirdinvert", "wiv",  P_BOOL|P_VI_DEF|P_RCLR,
			    (char_u *)&p_wiv, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[403] = (struct vimoption) {"whichwrap",   "ww",   P_STRING|P_VIM|P_ONECOMMA|P_FLAGLIST,
			    (char_u *)&p_ww, PV_NONE,
			    {(char_u *)"", (char_u *)"b,s"} SCTX_INIT},
options[404] = (struct vimoption) {"wildchar",    "wc",   P_NUM|P_VIM,
			    (char_u *)&p_wc, PV_NONE,
			    {(char_u *)(long)Ctrl_E, (char_u *)(long)TAB}
			    SCTX_INIT},
options[405] = (struct vimoption) {"wildcharm",   "wcm",  P_NUM|P_VI_DEF,
			    (char_u *)&p_wcm, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[406] = (struct vimoption) {"wildignore",  "wig",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
#ifdef FEAT_WILDIGN
			    (char_u *)&p_wig, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)"", (char_u *)0L} SCTX_INIT},
options[407] = (struct vimoption) {"wildignorecase", "wic", P_BOOL|P_VI_DEF,
			    (char_u *)&p_wic, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[408] = (struct vimoption) {"wildmenu",    "wmnu", P_BOOL|P_VI_DEF,
#ifdef FEAT_WILDMENU
			    (char_u *)&p_wmnu, PV_NONE,
#else
			    (char_u *)NULL, PV_NONE,
#endif
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[409] = (struct vimoption) {"wildmode",    "wim",  P_STRING|P_VI_DEF|P_ONECOMMA|P_NODUP,
			    (char_u *)&p_wim, PV_NONE,
			    {(char_u *)"full", (char_u *)0L} SCTX_INIT},
options[410] = (struct vimoption) {"wildoptions", "wop",  P_STRING|P_VI_DEF,
			    (char_u *)&p_wop, PV_NONE,
			    {(char_u *)"", (char_u *)0L}
			    SCTX_INIT},
options[411] = (struct vimoption) {"winaltkeys",  "wak",  P_STRING|P_VI_DEF,
#ifdef FEAT_WAK
			    (char_u *)&p_wak, PV_NONE,
			    {(char_u *)"menu", (char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)NULL, (char_u *)0L}
#endif
			    SCTX_INIT},
options[412] = (struct vimoption) {"wincolor", "wcr",	    P_STRING|P_ALLOCED|P_VI_DEF|P_RWIN,
			    (char_u *)VAR_WIN, PV_WCR,
			    {(char_u *)"", (char_u *)NULL}
			    SCTX_INIT},
options[413] = (struct vimoption) {"window",	    "wi",   P_NUM|P_VI_DEF,
			    (char_u *)&p_window, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[414] = (struct vimoption) {"winheight",   "wh",   P_NUM|P_VI_DEF,
			    (char_u *)&p_wh, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[415] = (struct vimoption) {"winfixheight", "wfh", P_BOOL|P_VI_DEF|P_RSTAT,
			    (char_u *)VAR_WIN, PV_WFH,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[416] = (struct vimoption) {"winfixwidth", "wfw", P_BOOL|P_VI_DEF|P_RSTAT,
			    (char_u *)VAR_WIN, PV_WFW,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[417] = (struct vimoption) {"winminheight", "wmh", P_NUM|P_VI_DEF,
			    (char_u *)&p_wmh, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[418] = (struct vimoption) {"winminwidth", "wmw", P_NUM|P_VI_DEF,
			    (char_u *)&p_wmw, PV_NONE,
			    {(char_u *)1L, (char_u *)0L} SCTX_INIT},
options[419] = (struct vimoption) {"winptydll", NULL,	    P_STRING|P_EXPAND|P_VI_DEF|P_SECURE,
#if defined(MSWIN) && defined(FEAT_TERMINAL)
			    (char_u *)&p_winptydll, PV_NONE, {
# ifdef _WIN64
			    (char_u *)"winpty64.dll",
# else
			    (char_u *)"winpty32.dll",
# endif
				(char_u *)0L}
#else
			    (char_u *)NULL, PV_NONE,
			    {(char_u *)0L, (char_u *)0L}
#endif
			    SCTX_INIT},
options[420] = (struct vimoption) {"winwidth",   "wiw",   P_NUM|P_VI_DEF,
			    (char_u *)&p_wiw, PV_NONE,
			    {(char_u *)20L, (char_u *)0L} SCTX_INIT},
options[421] = (struct vimoption) {"wrap",	    NULL,   P_BOOL|P_VI_DEF|P_RWIN,
			    (char_u *)VAR_WIN, PV_WRAP,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[422] = (struct vimoption) {"wrapmargin",  "wm",   P_NUM|P_VI_DEF,
			    (char_u *)&p_wm, PV_WM,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[423] = (struct vimoption) {"wrapscan",    "ws",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_ws, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[424] = (struct vimoption) {"write",	    NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_write, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},
options[425] = (struct vimoption) {"writeany",    "wa",   P_BOOL|P_VI_DEF,
			    (char_u *)&p_wa, PV_NONE,
			    {(char_u *)FALSE, (char_u *)0L} SCTX_INIT},
options[426] = (struct vimoption) {"writebackup", "wb",   P_BOOL|P_VI_DEF|P_VIM,
			    (char_u *)&p_wb, PV_NONE,
			    {
#ifdef FEAT_WRITEBACKUP
			    (char_u *)TRUE,
#else
			    (char_u *)FALSE,
#endif
				(char_u *)0L} SCTX_INIT},
options[427] = (struct vimoption) {"writedelay",  "wd",   P_NUM|P_VI_DEF,
			    (char_u *)&p_wd, PV_NONE,
			    {(char_u *)0L, (char_u *)0L} SCTX_INIT},
options[428] = (struct vimoption) {"xtermcodes",  NULL,   P_BOOL|P_VI_DEF,
			    (char_u *)&p_xtermcodes, PV_NONE,
			    {(char_u *)TRUE, (char_u *)0L} SCTX_INIT},

// terminal output codes
#define my_p_term(sss, vvv)   {sss, NULL, P_STRING|P_VI_DEF|P_RALL|P_SECURE, \
			    (char_u *)&vvv, PV_NONE, \
			    {(char_u *)"", (char_u *)0L} SCTX_INIT};

options[429] = (struct vimoption) my_p_term("t_AB", T_CAB)
options[430] = (struct vimoption) my_p_term("t_AF", T_CAF)
options[431] = (struct vimoption) my_p_term("t_AU", T_CAU)
options[432] = (struct vimoption) my_p_term("t_AL", T_CAL)
options[433] = (struct vimoption) my_p_term("t_al", T_AL)
options[434] = (struct vimoption) my_p_term("t_bc", T_BC)
options[435] = (struct vimoption) my_p_term("t_BE", T_BE)
options[436] = (struct vimoption) my_p_term("t_BD", T_BD)
options[437] = (struct vimoption) my_p_term("t_cd", T_CD)
options[438] = (struct vimoption) my_p_term("t_ce", T_CE)
options[439] = (struct vimoption) my_p_term("t_cl", T_CL)
options[440] = (struct vimoption) my_p_term("t_cm", T_CM)
options[441] = (struct vimoption) my_p_term("t_Ce", T_UCE)
options[442] = (struct vimoption) my_p_term("t_Co", T_CCO)
options[443] = (struct vimoption) my_p_term("t_CS", T_CCS)
options[444] = (struct vimoption) my_p_term("t_Cs", T_UCS)
options[445] = (struct vimoption) my_p_term("t_cs", T_CS)
options[446] = (struct vimoption) my_p_term("t_CV", T_CSV)
options[447] = (struct vimoption) my_p_term("t_da", T_DA)
options[448] = (struct vimoption) my_p_term("t_db", T_DB)
options[449] = (struct vimoption) my_p_term("t_DL", T_CDL)
options[450] = (struct vimoption) my_p_term("t_dl", T_DL)
options[451] = (struct vimoption) my_p_term("t_EC", T_CEC)
options[452] = (struct vimoption) my_p_term("t_EI", T_CEI)
options[453] = (struct vimoption) my_p_term("t_fs", T_FS)
options[454] = (struct vimoption) my_p_term("t_fd", T_FD)
options[455] = (struct vimoption) my_p_term("t_fe", T_FE)
options[456] = (struct vimoption) my_p_term("t_GP", T_CGP)
options[457] = (struct vimoption) my_p_term("t_IE", T_CIE)
options[458] = (struct vimoption) my_p_term("t_IS", T_CIS)
options[459] = (struct vimoption) my_p_term("t_ke", T_KE)
options[460] = (struct vimoption) my_p_term("t_ks", T_KS)
options[461] = (struct vimoption) my_p_term("t_le", T_LE)
options[462] = (struct vimoption) my_p_term("t_mb", T_MB)
options[463] = (struct vimoption) my_p_term("t_md", T_MD)
options[464] = (struct vimoption) my_p_term("t_me", T_ME)
options[465] = (struct vimoption) my_p_term("t_mr", T_MR)
options[466] = (struct vimoption) my_p_term("t_ms", T_MS)
options[467] = (struct vimoption) my_p_term("t_nd", T_ND)
options[468] = (struct vimoption) my_p_term("t_op", T_OP)
options[469] = (struct vimoption) my_p_term("t_RF", T_RFG)
options[470] = (struct vimoption) my_p_term("t_RB", T_RBG)
options[471] = (struct vimoption) my_p_term("t_RC", T_CRC)
options[472] = (struct vimoption) my_p_term("t_RI", T_CRI)
options[473] = (struct vimoption) my_p_term("t_Ri", T_SRI)
options[474] = (struct vimoption) my_p_term("t_RS", T_CRS)
options[475] = (struct vimoption) my_p_term("t_RT", T_CRT)
options[476] = (struct vimoption) my_p_term("t_RV", T_CRV)
options[477] = (struct vimoption) my_p_term("t_Sb", T_CSB)
options[478] = (struct vimoption) my_p_term("t_SC", T_CSC)
options[479] = (struct vimoption) my_p_term("t_se", T_SE)
options[480] = (struct vimoption) my_p_term("t_Sf", T_CSF)
options[481] = (struct vimoption) my_p_term("t_SH", T_CSH)
options[482] = (struct vimoption) my_p_term("t_SI", T_CSI)
options[483] = (struct vimoption) my_p_term("t_Si", T_SSI)
options[484] = (struct vimoption) my_p_term("t_so", T_SO)
options[485] = (struct vimoption) my_p_term("t_SR", T_CSR)
options[486] = (struct vimoption) my_p_term("t_sr", T_SR)
options[487] = (struct vimoption) my_p_term("t_ST", T_CST)
options[488] = (struct vimoption) my_p_term("t_Te", T_STE)
options[489] = (struct vimoption) my_p_term("t_te", T_TE)
options[490] = (struct vimoption) my_p_term("t_TE", T_CTE)
options[491] = (struct vimoption) my_p_term("t_ti", T_TI)
options[492] = (struct vimoption) my_p_term("t_TI", T_CTI)
options[493] = (struct vimoption) my_p_term("t_Ts", T_STS)
options[494] = (struct vimoption) my_p_term("t_ts", T_TS)
options[495] = (struct vimoption) my_p_term("t_u7", T_U7)
options[496] = (struct vimoption) my_p_term("t_ue", T_UE)
options[497] = (struct vimoption) my_p_term("t_us", T_US)
options[498] = (struct vimoption) my_p_term("t_ut", T_UT)
options[499] = (struct vimoption) my_p_term("t_vb", T_VB)
options[500] = (struct vimoption) my_p_term("t_ve", T_VE)
options[501] = (struct vimoption) my_p_term("t_vi", T_VI)
options[502] = (struct vimoption) my_p_term("t_VS", T_CVS)
options[503] = (struct vimoption) my_p_term("t_vs", T_VS)
options[504] = (struct vimoption) my_p_term("t_WP", T_CWP)
options[505] = (struct vimoption) my_p_term("t_WS", T_CWS)
options[506] = (struct vimoption) my_p_term("t_xn", T_XN)
options[507] = (struct vimoption) my_p_term("t_xs", T_XS)
options[508] = (struct vimoption) my_p_term("t_ZH", T_CZH)
options[509] = (struct vimoption) my_p_term("t_ZR", T_CZR)
options[510] = (struct vimoption) my_p_term("t_8f", T_8F)
options[511] = (struct vimoption) my_p_term("t_8b", T_8B)
options[512] = (struct vimoption) my_p_term("t_8u", T_8U)

// terminal key codes are not in here

    // end marker
options[513] = (struct vimoption) {NULL, NULL, 0, NULL, PV_NONE, {NULL, NULL} SCTX_INIT};
// };


// Also reset all local variables (these are from option.c): 
p_ai = 0;
p_bin = 0;
p_bomb = 0;
p_bh = NULL;
p_bt = NULL;
p_bl = 0;
p_ci = 0;
#ifdef FEAT_CINDENT
p_cin = 0;
p_cink = NULL;
p_cino = NULL;
#endif
#if defined(FEAT_SMARTINDENT) || defined(FEAT_CINDENT)
p_cinw = NULL;
#endif
#ifdef FEAT_COMMENTS
p_com = NULL;
#endif
#ifdef FEAT_FOLDING
p_cms = NULL;
#endif
#ifdef FEAT_INS_EXPAND
p_cpt = NULL;
#endif
#ifdef FEAT_COMPL_FUNC
p_cfu = NULL;
p_ofu = NULL;
#endif
#ifdef FEAT_EVAL
p_tfu = NULL;
#endif
p_eol = 0;
p_fixeol = 0;
p_et = 0;
p_fenc = NULL;
p_ff = NULL;
p_fo = NULL;
p_flp = NULL;
p_ft = NULL;
p_iminsert = 0;
p_imsearch = 0;
#if defined(FEAT_FIND_ID) && defined(FEAT_EVAL)
p_inex = NULL;
#endif
#if defined(FEAT_CINDENT) && defined(FEAT_EVAL)
p_inde = NULL;
p_indk = NULL;
#endif
#if defined(FEAT_EVAL)
p_fex = NULL;
#endif
p_inf = 0;
p_isk = NULL;
#ifdef FEAT_CRYPT
p_key = NULL;
#endif
#ifdef FEAT_LISP
p_lisp = 0;
#endif
p_ml = 0;
p_ma = 0;
p_mod = 0;
p_mps = NULL;
p_nf = NULL;
p_pi = 0;
#ifdef FEAT_TEXTOBJ
p_qe = NULL;
#endif
p_ro = 0;
#ifdef FEAT_SMARTINDENT
p_si = 0;
#endif
p_sn = 0;
p_sts = 0;
#if defined(FEAT_SEARCHPATH)
p_sua = NULL;
#endif
p_sw = 0;
p_swf = 0;
#ifdef FEAT_SYN_HL
p_smc = 0;
p_syn = NULL;
#endif
#ifdef FEAT_SPELL
p_spc = NULL;
p_spf = NULL;
p_spl = NULL;
#endif
p_ts = 0;
p_tw = 0;
p_tx = 0;
#ifdef FEAT_PERSISTENT_UNDO
p_udf = 0;
#endif
p_wm = 0;
#ifdef FEAT_VARTABS
// These need to be reset in options.c. Why?
p_vsts = empty_option;
p_vts = empty_option;
#endif
#ifdef FEAT_KEYMAP
p_keymap = NULL;
#endif
#ifdef FEAT_TERMINAL
p_twsl = 0;		/* 'termwinscroll' */
#endif

/* Saved values for when 'bin' is set. */
p_et_nobin = 0;
p_ml_nobin = 0;
p_tw_nobin = 0;
p_wm_nobin = 0;

/* Saved values for when 'paste' is set */
p_ai_nopaste = 0;
p_et_nopaste = 0;
p_sts_nopaste = 0;
p_tw_nopaste = 0;
p_wm_nopaste = 0;
#ifdef FEAT_VARTABS
p_vsts_nopaste = NULL; 
#endif

// Also reset all local variables (these are from option.h): 
/*
 * option.h: definition of global variables for settable options
 */
/*
 * The following are actual variables for the options
 */

#ifdef FEAT_RIGHTLEFT
p_aleph = 0;	// 'aleph'
#endif
#ifdef FEAT_AUTOCHDIR
p_acd = 0;		// 'autochdir'
#endif
p_ambw = NULL;	// 'ambiwidth'
p_emoji = NULL;	// 'emoji'
#if defined(FEAT_GUI) && defined(MACOS_X)
p_antialias = NULL;	// 'antialias'
#endif
p_ar = 0;		// 'autoread'
p_aw = 0;		// 'autowrite'
p_awa = 0;		// 'autowriteall'
p_bs = NULL;		// 'backspace'
p_bg = NULL;		// 'background'
p_bk = 0;		// 'backup'
p_bkc = NULL; 	// 'backupcopy'
bkc_flags = 0;	// flags from 'backupcopy'
p_bdir = NULL;	// 'backupdir'
p_bex = NULL;		// 'backupext'
p_bo = NULL;		// 'belloff'
bo_flags = 0;

#ifdef FEAT_WILDIGN
p_bsk = NULL;		// 'backupskip'
#endif
#ifdef FEAT_CRYPT
p_cm = NULL;		// 'cryptmethod'
#endif
#ifdef FEAT_BEVAL
# ifdef FEAT_BEVAL_GUI
p_beval = 0;	// 'ballooneval'
# endif
p_bdlay = 0;	// 'balloondelay'
# ifdef FEAT_EVAL
p_bexpr = NULL;
# endif
# ifdef FEAT_BEVAL_TERM
p_bevalterm = 0;	// 'balloonevalterm'
# endif
#endif
#ifdef FEAT_BROWSE
p_bsdir = NULL;	// 'browsedir'
#endif
#ifdef FEAT_LINEBREAK
p_breakat = NULL;	// 'breakat'
#endif
p_cmp = NULL;		// 'casemap'
cmp_flags = 0;
p_enc = NULL;		// 'encoding'
p_deco = 0;		// 'delcombine'
#ifdef FEAT_EVAL
p_ccv = NULL;		// 'charconvert'
#endif
#ifdef FEAT_CMDWIN
p_cedit = NULL;	// 'cedit'
p_cwh = 0;		// 'cmdwinheight'
#endif
#ifdef FEAT_CLIPBOARD
p_cb = NULL;		// 'clipboard'
#endif
p_ch = 0;		// 'cmdheight'
#if defined(FEAT_GUI_DIALOG) || defined(FEAT_CON_DIALOG)
p_confirm = 0;	// 'confirm'
#endif
p_cp = 0;		// 'compatible'
#ifdef FEAT_INS_EXPAND
p_cot = NULL;		// 'completeopt'
p_ph = 0;		// 'pumheight'
p_pw = 0;		// 'pumwidth'
#endif
p_cpo = NULL;		// 'cpoptions'
#ifdef FEAT_CSCOPE
p_csprg = NULL;	// 'cscopeprg'
p_csre = 0;		// 'cscoperelative'
# ifdef FEAT_QUICKFIX
p_csqf = NULL;	// 'cscopequickfix'
# endif
p_cst = 0;		// 'cscopetag'
p_csto = 0;		// 'cscopetagorder'
p_cspc = 0;		// 'cscopepathcomp'
p_csverbose = 0;	// 'cscopeverbose'
#endif
p_debug = NULL;	// 'debug'
#ifdef FEAT_FIND_ID
p_def = NULL;		// 'define'
p_inc = NULL;
#endif
#ifdef FEAT_DIFF
p_dip = NULL;		// 'diffopt'
# ifdef FEAT_EVAL
p_dex = NULL;		// 'diffexpr'
# endif
#endif
#ifdef FEAT_INS_EXPAND
p_dict = NULL;	// 'dictionary'
#endif
#ifdef FEAT_DIGRAPHS
p_dg = 0;		// 'digraph'
#endif
p_dir = NULL;		// 'directory'
p_dy = NULL;		// 'display'
dy_flags = 0;
p_ed = 0;		// 'edcompatible'
p_ead = NULL;		// 'eadirection'
p_ea = 0;		// 'equalalways'
p_ep = NULL;		// 'equalprg'
p_eb = 0;		// 'errorbells'
#ifdef FEAT_QUICKFIX
p_ef = NULL;		// 'errorfile'
p_efm = NULL;		// 'errorformat'
p_gefm = NULL;	// 'grepformat'
p_gp = NULL;		// 'grepprg'
#endif
p_ei = NULL;		// 'eventignore'
p_ek = 0;		// 'esckeys'
p_exrc = 0;		// 'exrc'
p_fencs = NULL;	// 'fileencodings'
p_ffs = NULL;		// 'fileformats'
p_fic = 0;		// 'fileignorecase'
#ifdef FEAT_FOLDING
p_fcl = NULL;		// 'foldclose'
p_fdls = 0;		// 'foldlevelstart'
p_fdo = NULL;		// 'foldopen'
fdo_flags = 0;
#endif
p_fp = NULL;		// 'formatprg'
#ifdef HAVE_FSYNC
p_fs = 0;		// 'fsync'
#endif
p_gd = 0;		// 'gdefault'
#ifdef FEAT_TEXT_PROP
p_pvp = NULL;		// 'previewpopup'
#endif
#ifdef FEAT_PRINTER
p_pdev = NULL;	// 'printdevice'
# ifdef FEAT_POSTSCRIPT
p_penc = NULL;	// 'printencoding'
p_pexpr = NULL;	// 'printexpr'
p_pmfn = NULL;	// 'printmbfont'
p_pmcs = NULL;	// 'printmbcharset'
# endif
p_pfn = NULL;		// 'printfont'
p_popt = NULL;	// 'printoptions'
p_header = NULL;	// 'printheader'
#endif
p_prompt = 0;	// 'prompt'
#ifdef FEAT_GUI
p_guifont = NULL;	// 'guifont'
# ifdef FEAT_XFONTSET
p_guifontset = NULL;	// 'guifontset'
# endif
p_guifontwide = NULL;	// 'guifontwide'
p_guipty = 0;	// 'guipty'
#endif
#if defined(FEAT_GUI_GTK) || defined(FEAT_GUI_X11)
p_ghr = 0;		// 'guiheadroom'
#endif
#ifdef CURSOR_SHAPE
p_guicursor = NULL;	// 'guicursor'
#endif
#ifdef FEAT_MOUSESHAPE
p_mouseshape = NULL;	// 'mouseshape'
#endif
#if defined(FEAT_GUI)
p_go = NULL;		// 'guioptions'
#endif
#if defined(FEAT_GUI_TABLINE)
p_gtl = NULL;		// 'guitablabel'
p_gtt = NULL;		// 'guitabtooltip'
#endif
p_hf = NULL;		// 'helpfile'
p_hh = 0;		// 'helpheight'
#ifdef FEAT_MULTI_LANG
p_hlg = NULL;		// 'helplang'
#endif
p_hid = 0;		// 'hidden'
p_hl = NULL;		// 'highlight'
p_hls = 0;		// 'hlsearch'
p_hi = 0;		// 'history'
#ifdef FEAT_RIGHTLEFT
p_hkmap = 0;	// 'hkmap'
p_hkmapp = 0;	// 'hkmapp'
# ifdef FEAT_ARABIC
p_arshape = 0;	// 'arabicshape'
# endif
#endif
#ifdef FEAT_TITLE
p_icon = 0;		// 'icon'
p_iconstring = NULL;	// 'iconstring'
#endif
p_ic = 0;		// 'ignorecase'
#if defined(FEAT_XIM) && defined(FEAT_GUI_GTK)
p_imak = NULL;	// 'imactivatekey'
p_imst = 0;		// 'imstyle'
#endif
#if defined(FEAT_EVAL)
p_imaf = NULL;	// 'imactivatefunc'
p_imsf = NULL;	// 'imstatusfunc'
#endif
p_imcmdline = 0;	// 'imcmdline'
p_imdisable = 0;	// 'imdisable'
p_is = 0;		// 'incsearch'
p_im = 0;		// 'insertmode'
p_isf = NULL;		// 'isfname'
p_isi = NULL;		// 'isident'
p_isp = NULL;		// 'isprint'
p_js = 0;		// 'joinspaces'
p_kp = NULL;		// 'keywordprg'
p_km = NULL;		// 'keymodel'
#ifdef FEAT_LANGMAP
p_langmap = NULL;	// 'langmap'
p_lnr = 0;		// 'langnoremap'
p_lrm = 0;		// 'langremap'
#endif
#if defined(FEAT_MENU) && defined(FEAT_MULTI_LANG)
p_lm = NULL;		// 'langmenu'
#endif
#ifdef FEAT_GUI
p_linespace = 0;	// 'linespace'
#endif
#ifdef FEAT_LISP
p_lispwords = NULL;	// 'lispwords'
#endif
p_ls = 0;		// 'laststatus'
p_stal = 0;		// 'showtabline'
p_lcs = NULL;		// 'listchars'

p_lz = 0;		// 'lazyredraw'
p_lpl = 0;		// 'loadplugins'
#if defined(DYNAMIC_LUA)
p_luadll = NULL;	// 'luadll'
#endif
#ifdef FEAT_GUI_MAC
p_macatsui = 0;	// 'macatsui'
#endif
p_magic = 0;	// 'magic'
p_menc = NULL;	// 'makeencoding'
#ifdef FEAT_QUICKFIX
p_mef = NULL;		// 'makeef'
p_mp = NULL;		// 'makeprg'
#endif
p_mat = 0;		// 'matchtime'
p_mco = 0;		// 'maxcombine'
#ifdef FEAT_EVAL
p_mfd = 0;		// 'maxfuncdepth'
#endif
p_mmd = 0;		// 'maxmapdepth'
p_mm = 0;		// 'maxmem'
p_mmp = 0;		// 'maxmempattern'
p_mmt = 0;		// 'maxmemtot'
#ifdef FEAT_MENU
p_mis = 0;		// 'menuitems'
#endif
#ifdef FEAT_SPELL
p_msm = NULL;		// 'mkspellmem'
#endif
p_mle = 0;		// 'modelineexpr'
p_mls = 0;		// 'modelines'
p_mouse = NULL;	// 'mouse'
#ifdef FEAT_GUI
p_mousef = 0;	// 'mousefocus'
p_mh = 0;		// 'mousehide'
#endif
p_mousem = NULL;	// 'mousemodel'
p_mouset = 0;	// 'mousetime'
p_more = 0;		// 'more'
#ifdef FEAT_MZSCHEME
p_mzq = 0;		// 'mzquantum
# if defined(DYNAMIC_MZSCHEME)
p_mzschemedll = NULL;	// 'mzschemedll'
p_mzschemegcdll = NULL; // 'mzschemegcdll'
# endif
#endif
#if defined(MSWIN)
p_odev = 0;		// 'opendevice'
#endif
p_opfunc = NULL;	// 'operatorfunc'
p_para = NULL;	// 'paragraphs'
p_paste = 0;	// 'paste'
p_pt = NULL;		// 'pastetoggle'
#if defined(FEAT_EVAL) && defined(FEAT_DIFF)
p_pex = NULL;		// 'patchexpr'
#endif
p_pm = NULL;		// 'patchmode'
p_path = NULL;	// 'path'
#ifdef FEAT_SEARCHPATH
p_cdpath = NULL;	// 'cdpath'
#endif
#if defined(DYNAMIC_PERL)
p_perldll = NULL;	// 'perldll'
#endif
#if defined(DYNAMIC_PYTHON3)
p_py3dll = NULL;	// 'pythonthreedll'
#endif
#ifdef FEAT_PYTHON3
p_py3home = NULL;	// 'pythonthreehome'
#endif
#if defined(DYNAMIC_PYTHON)
p_pydll = NULL;	// 'pythondll'
#endif
#ifdef FEAT_PYTHON
p_pyhome = NULL;	// 'pythonhome'
#endif
#if defined(FEAT_PYTHON) || defined(FEAT_PYTHON3)
p_pyx = 0;		// 'pyxversion'
#endif
#ifdef FEAT_RELTIME
p_rdt = 0;		// 'redrawtime'
#endif
p_remap = 0;	// 'remap'
p_re = 0;		// 'regexpengine'
#ifdef FEAT_RENDER_OPTIONS
p_rop = NULL;		// 'renderoptions'
#endif
p_report = 0;	// 'report'
#if defined(FEAT_QUICKFIX)
p_pvh = 0;		// 'previewheight'
#endif
#ifdef MSWIN
p_rs = 0;		// 'restorescreen'
#endif
#ifdef FEAT_RIGHTLEFT
p_ari = 0;		// 'allowrevins'
p_ri = 0;		// 'revins'
#endif
#if defined(DYNAMIC_RUBY)
p_rubydll = NULL;	// 'rubydll'
#endif
#ifdef FEAT_CMDL_INFO
p_ru = 0;		// 'ruler'
#endif
#ifdef FEAT_STL_OPT
p_ruf = NULL;		// 'rulerformat'
#endif
p_pp = NULL;		// 'packpath'
p_rtp = NULL;		// 'runtimepath'
p_sj = 0;		// 'scrolljump'
p_so = 0;		// 'scrolloff'
p_sbo = NULL;		// 'scrollopt'
p_sections = NULL;	// 'sections'
p_secure = 0;	// 'secure'
p_sel = NULL;		// 'selection'
p_slm = NULL;		// 'selectmode'
#ifdef FEAT_SESSION
p_ssop = NULL;	// 'sessionoptions'
ssop_flags = 0;
#endif
p_sh = NULL;		// 'shell'
p_shcf = NULL;	// 'shellcmdflag'
#ifdef FEAT_QUICKFIX
p_sp = NULL;		// 'shellpipe'
#endif
p_shq = NULL;		// 'shellquote'
p_sxq = NULL;		// 'shellxquote'
p_sxe = NULL;		// 'shellxescape'
p_srr = NULL;		// 'shellredir'
#ifdef AMIGA
p_st = 0;		// 'shelltype'
#endif
p_stmp = 0;		// 'shelltemp'
#ifdef BACKSLASH_IN_FILENAME
p_ssl = 0;		// 'shellslash'
#endif
#ifdef FEAT_STL_OPT
p_stl = NULL;		// 'statusline'
#endif
p_sr = 0;		// 'shiftround'
p_shm = NULL;		// 'shortmess'
#ifdef FEAT_LINEBREAK
p_sbr = NULL;		// 'showbreak'
#endif
#ifdef FEAT_CMDL_INFO
p_sc = 0;		// 'showcmd'
#endif
p_sft = 0;		// 'showfulltag'
p_sm = 0;		// 'showmatch'
p_smd = 0;		// 'showmode'
p_ss = 0;		// 'sidescroll'
p_siso = 0;		// 'sidescrolloff'
p_scs = 0;		// 'smartcase'
p_sta = 0;		// 'smarttab'
p_sb = 0;		// 'splitbelow'
p_tpm = 0;		// 'tabpagemax'
# if defined(FEAT_STL_OPT)
p_tal = NULL;		// 'tabline'
# endif
#ifdef FEAT_SPELL
p_sps = NULL;		// 'spellsuggest'
#endif
p_spr = 0;		// 'splitright'
p_sol = 0;		// 'startofline'
p_su = NULL;		// 'suffixes'
p_sws = NULL;		// 'swapsync'
p_swb = NULL;		// 'switchbuf'
swb_flags = 0;
p_tbs = 0;		// 'tagbsearch'
p_tc = NULL;		// 'tagcase'
tc_flags = 0;       // flags from 'tagcase'
p_tl = 0;		// 'taglength'
p_tr = 0;		// 'tagrelative'
p_tags = NULL;	// 'tags'
p_tgst = 0;		// 'tagstack'
#if defined(DYNAMIC_TCL)
p_tcldll = NULL;	// 'tcldll'
#endif
#ifdef FEAT_ARABIC
p_tbidi = 0;	// 'termbidi'
#endif
p_tenc = NULL;	// 'termencoding'
#ifdef FEAT_TERMGUICOLORS
p_tgc = 0;		// 'termguicolors'
#endif
#if defined(MSWIN) && defined(FEAT_TERMINAL)
p_twt = NULL;		// 'termwintype'
#endif
p_terse = 0;	// 'terse'
p_ta = 0;		// 'textauto'
p_to = 0;		// 'tildeop'
p_timeout = 0;	// 'timeout'
p_tm = 0;		// 'timeoutlen'
#ifdef FEAT_TITLE
p_title = 0;	// 'title'
p_titlelen = 0;	// 'titlelen'
p_titleold = NULL;	// 'titleold'
p_titlestring = NULL;	// 'titlestring'
#endif
#ifdef FEAT_INS_EXPAND
p_tsr = NULL;		// 'thesaurus'
#endif
p_ttimeout = 0;	// 'ttimeout'
p_ttm = 0;		// 'ttimeoutlen'
p_tbi = 0;		// 'ttybuiltin'
p_tf = 0;		// 'ttyfast'
#if defined(FEAT_TOOLBAR) && !defined(FEAT_GUI_MSWIN)
p_toolbar = NULL;	// 'toolbar'
toolbar_flags = 0;
#endif
#if defined(FEAT_TOOLBAR) && defined(FEAT_GUI_GTK)
p_tbis = NULL;	// 'toolbariconsize'
tbis_flags = 0;
#endif
p_ttyscroll = 0;	// 'ttyscroll'
#if defined(FEAT_MOUSE) && (defined(UNIX) || defined(VMS))
p_ttym = NULL;	// 'ttymouse'
ttym_flags = 0;
#endif
p_udir = NULL;	// 'undodir'
p_ul = 0;		// 'undolevels'
p_ur = 0;		// 'undoreload'
p_uc = 0;		// 'updatecount'
p_ut = 0;		// 'updatetime'
p_fcs = NULL;		// 'fillchar'
#ifdef FEAT_VIMINFO
p_viminfo = NULL;	// 'viminfo'
p_viminfofile = NULL;	// 'viminfofile'
#endif
#ifdef FEAT_SESSION
p_vdir = NULL;	// 'viewdir'
p_vop = NULL;		// 'viewoptions'
vop_flags = 0;	// uses SSOP_ flags
#endif
p_vb = 0;		// 'visualbell'
p_ve = NULL;		// 'virtualedit'
ve_flags = 0;
p_verbose = 0;	// 'verbose' 
#ifdef IN_OPTION_C
p_vfile = (char_u *)""; // used before options are initialized
#else
p_vfile = NULL;	// 'verbosefile'
#endif
p_warn = 0;		// 'warn'
#ifdef FEAT_CMDL_COMPL
p_wop = NULL;		// 'wildoptions'
#endif
p_window = 0;	// 'window'
#if defined(FEAT_GUI_MSWIN) || defined(FEAT_GUI_MOTIF) || defined(LINT) \
	|| defined (FEAT_GUI_GTK) || defined(FEAT_GUI_PHOTON)
#define FEAT_WAK
p_wak = NULL;		// 'winaltkeys'
#endif
#ifdef FEAT_WILDIGN
p_wig = NULL;		// 'wildignore'
#endif
p_wiv = 0;		// 'weirdinvert'
p_ww = NULL;		// 'whichwrap'
p_wc = 0;		// 'wildchar'
p_wcm = 0;		// 'wildcharm'
p_wic = 0;		// 'wildignorecase'
p_wim = NULL;		// 'wildmode'
#ifdef FEAT_WILDMENU
p_wmnu = 0;		// 'wildmenu'
#endif
p_wh = 0;		// 'winheight'
p_wmh = 0;		// 'winminheight'
p_wmw = 0;		// 'winminwidth'
p_wiw = 0;		// 'winwidth'
#if defined(MSWIN) && defined(FEAT_TERMINAL)
p_winptydll = NULL;	// 'winptydll'
#endif
p_ws = 0;		// 'wrapscan'
p_write = 0;	// 'write'
p_wa = 0;		// 'writeany'
p_wb = 0;		// 'writebackup'
p_wd = 0;		// 'writedelay'



