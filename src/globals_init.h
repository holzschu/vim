/* vi:set ts=8 sts=4 sw=4 noet:
 *
 * VIM - Vi IMproved	by Bram Moolenaar
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 */

/*
 * initialization of global variables
 */

Rows    = 24L; // nr of rows in the screen
Columns = 80;	// nr of columns in the screen
ScreenLines = NULL;
ScreenAttrs = NULL;
LineOffset = NULL;
LineWraps = NULL;	// line wraps to next line
ScreenLinesUC = NULL;	// decoded UTF-8 characters
Screen_mco = 0;		// value of p_mco used when
ScreenLines2 = NULL;
current_ScreenLine = NULL;
screen_cur_row = 0;
screen_cur_col = 0;
redrawing_for_callback = 0;
TabPageIdxs = NULL;
#ifdef FEAT_TEXT_PROP
// Array with size Rows x Columns containing zindex of popups.
popup_mask = NULL;
popup_mask_next = NULL;
// Array with flags for tansparent cells of current popup.
popup_transparent = NULL;
// Flag set to TRUE when popup_mask needs to be updated.
popup_mask_refresh = TRUE;
// Tab that was used to fill popup_mask.
popup_mask_tab = NULL;
// Zindex in for screen_char(): if lower than the value in "popup_mask"
// drawing the character is skipped.
screen_zindex = 0;
#endif
screen_Rows = 0;	    // actual size of ScreenLines[]
screen_Columns = 0;   // actual size of ScreenLines[]
mod_mask = 0x0;		// current key modifiers
cmdline_row = 0;
redraw_cmdline = FALSE;	// cmdline must be redrawn
redraw_mode = FALSE;	// mode must be redrawn
clear_cmdline = FALSE;	// cmdline must be cleared
mode_displayed = FALSE;	// mode is being displayed
no_win_do_lines_ins = FALSE; // don't insert lines
#if defined(FEAT_CRYPT) || defined(FEAT_EVAL)
cmdline_star = FALSE;	// cmdline is crypted
#endif
exec_from_reg = FALSE;	// executing register
screen_cleared = FALSE;	// screen has been cleared
dollar_vcol = -1;
compl_length = 0;
compl_cont_status = 0;
edit_submode = NULL; // msg for CTRL-X submode
edit_submode_pre = NULL; // prepended to edit_submode
edit_submode_extra = NULL;// appended to edit_submode
edit_submode_highl = 0;	// highl. method for extra info
#ifdef FEAT_RIGHTLEFT
cmdmsg_rl = FALSE;    // cmdline is drawn right to left
#endif
msg_col = 0;
msg_row = 0;
msg_scrolled = 0;	// Number of screen lines that windows have
				// scrolled because of printing messages.
msg_scrolled_ign = FALSE;
				// when TRUE don't set need_wait_return in
				// msg_puts_attr() when msg_scrolled is
				// non-zero

keep_msg = NULL;	    // msg to be shown after redraw
keep_msg_attr = 0;    // highlight attr for keep_msg
keep_msg_more = FALSE; // keep_msg was set by msgmore()
need_fileinfo = FALSE;// do fileinfo() after redraw
msg_scroll = FALSE;   // msg_start() will scroll
msg_didout = FALSE;   // msg_outstr() was used in line
msg_didany = FALSE;   // msg_outstr() was used at all
msg_nowait = FALSE;   // don't wait for this msg
emsg_off = 0;	    // don't display errors for now,
					    // unless 'debug' is set.
info_message = FALSE; // printing informative message
msg_hist_off = FALSE; // don't add messages to history
#ifdef FEAT_EVAL
need_clr_eos = FALSE; // need to clear text before
				    // displaying a message.
emsg_skip = 0;	    // don't display errors for
				    // expression that is skipped
emsg_severe = FALSE;  // use message of next of several
				    // emsg() calls for throw
did_endif = FALSE;    // just had ":endif"
#endif
did_emsg = 0;		    // set by emsg() when the message
					    // is displayed or thrown
#ifdef FEAT_EVAL
called_vim_beep = 0;	    // set if vim_beep() is called
did_uncaught_emsg = 0;	    // emsg() was called and did not
					    // cause an exception
#endif
did_emsg_syntax = 0;	    // did_emsg set because of a
					    // syntax error
called_emsg = 0;		    // always set by emsg()
ex_exitval = 0;	    // exit value for ex mode
emsg_on_display = FALSE;	// there is an error message
rc_did_emsg = FALSE;  // vim_regcomp() called emsg()

no_wait_return = 0;   // don't wait for return for now
need_wait_return = 0; // need to wait for return later
did_wait_return = FALSE;	// wait_return() was used and
						// nothing written since then
#ifdef FEAT_TITLE
need_maketitle = TRUE; // call maketitle() soon
#endif

quit_more = FALSE;    // 'q' hit at "--more--" msg
#if defined(UNIX) || defined(VMS) || defined(MACOS_X)
newline_on_exit = FALSE;	// did msg in altern. screen
intr_char = 0;	    // extra interrupt character
#endif
#if (defined(UNIX) || defined(VMS)) && defined(FEAT_X11)
x_no_connect = FALSE; // don't connect to X server
# if defined(FEAT_CLIENTSERVER)
x_force_connect = FALSE;	// Do connect to X server.
						// Overrules x_no_connect and
						// "exclude" in 'clipboard'.
# endif
#endif
ex_keep_indent = FALSE; // getexmodeline(): keep indent
vgetc_busy = 0;	      // when inside vgetc() then > 0

didset_vim = FALSE;	    // did set $VIM ourselves
didset_vimruntime = FALSE;    // idem for $VIMRUNTIME

/*
 * Lines left before a "more" message.	Ex mode needs to be able to reset this
 * after you type something.
 */
lines_left = -1;	    // lines left for listing
msg_no_more = FALSE;  // don't use more prompt, truncate
					    // messages

sourcing_name  = NULL;// name of error message source
linenr_T	sourcing_lnum = 0;    // line number of the source file

#ifdef FEAT_EVAL
ex_nesting_level = 0;	// nesting level
debug_break_level = -1;	// break below this level
debug_did_msg = FALSE;	// did "debug mode" message
debug_tick = 0;		// breakpoint change count
debug_backtrace_level = 0; // breakpoint backtrace level
# ifdef FEAT_PROFILE
do_profiling = PROF_NONE;	// PROF_ values
# endif
script_items = (garray_T) {0 COMMA 0 COMMA sizeof(scriptitem_T) COMMA 4 COMMA NULL};

/*
 * The exception currently being thrown.  Used to pass an exception to
 * a different cstack.  Also used for discarding an exception before it is
 * caught or made pending.  Only valid when did_throw is TRUE.
 */
current_exception = NULL;

/*
 * did_throw: An exception is being thrown.  Reset when the exception is caught
 * or as long as it is pending in a finally clause.
 */
did_throw = FALSE;

/*
 * need_rethrow: set to TRUE when a throw that cannot be handled in do_cmdline()
 * must be propagated to the cstack of the previously called do_cmdline().
 */
need_rethrow = FALSE;

/*
 * check_cstack: set to TRUE when a ":finish" or ":return" that cannot be
 * handled in do_cmdline() must be propagated to the cstack of the previously
 * called do_cmdline().
 */
check_cstack = FALSE;

/*
 * Number of nested try conditionals (across function calls and ":source"
 * commands).
 */
trylevel = 0;

/*
 * When "force_abort" is TRUE, always skip commands after an error message,
 * even after the outermost ":endif", ":endwhile" or ":endfor" or for a
 * function without the "abort" flag.  It is set to TRUE when "trylevel" is
 * non-zero (and ":silent!" was not used) or an exception is being thrown at
 * the time an error is detected.  It is set to FALSE when "trylevel" gets
 * zero again and there was no error or interrupt or throw.
 */
force_abort = FALSE;

/*
 * "msg_list" points to a variable in the stack of do_cmdline() which keeps
 * the list of arguments of several emsg() calls, one of which is to be
 * converted to an error exception immediately after the failing command
 * returns.  The message to be used for the exception value is pointed to by
 * the "throw_msg" field of the first element in the list.  It is usually the
 * same as the "msg" field of that element, but can be identical to the "msg"
 * field of a later list element, when the "emsg_severe" flag was set when the
 * emsg() call was made.
 */
msg_list = NULL;

/*
 * suppress_errthrow: When TRUE, don't convert an error to an exception.  Used
 * when displaying the interrupt message or reporting an exception that is still
 * uncaught at the top level (which has already been discarded then).  Also used
 * for the error message when no exception can be thrown.
 */
suppress_errthrow = FALSE;

/*
 * The stack of all caught and not finished exceptions.  The exception on the
 * top of the stack is the one got by evaluation of v:exception.  The complete
 * stack of all caught and pending exceptions is embedded in the various
 * cstacks; the pending exceptions, however, are not on the caught stack.
 */
caught_stack = NULL;

#endif

#ifdef FEAT_EVAL
/*
 * Garbage collection can only take place when we are sure there are no Lists
 * or Dictionaries being used internally.  This is flagged with
 * "may_garbage_collect" when we are at the toplevel.
 * "want_garbage_collect" is set by the garbagecollect() function, which means
 * we do garbage collection before waiting for a char at the toplevel.
 * "garbage_collect_at_exit" indicates garbagecollect(1) was called.
 */
may_garbage_collect = FALSE;
want_garbage_collect = FALSE;
garbage_collect_at_exit = FALSE;

// Script CTX being sourced or was sourced to define the current function.
current_sctx = (sctx_T) {0 COMMA 0 COMMA 0 COMMA 0};
#endif

did_source_packages = FALSE;

// Magic number used for hashitem "hi_key" value indicating a deleted item.
// Only the address is used.
hash_removed = NUL;


scroll_region = FALSE; // term supports scroll region
t_colors = 0;	    // int value of T_CCO

// Flags to indicate an additional string for highlight name completion.
include_none = 0;	// when 1 include "None"
include_default = 0;	// when 1 include "default"
include_link = 0;	// when 2 include "link" and "clear"

/*
 * When highlight_match is TRUE, highlight a match, starting at the cursor
 * position.  Search_match_lines is the number of lines after the match (0 for
 * a match within one line), search_match_endcol the column number of the
 * character just after the match in the last line.
 */
highlight_match = FALSE;	// show search match pos
search_match_lines = 0;		// lines of of matched string
search_match_endcol = 0;		// col nr of match end
#ifdef FEAT_SEARCH_EXTRA
search_first_line = 0;	  // for :{FIRST},{last}s/pat
search_last_line = MAXLNUM; // for :{first},{LAST}s/pat
#endif

no_smartcase = FALSE;	// don't use 'smartcase' once

need_check_timestamps = FALSE; // need to check file
						     // timestamps asap
did_check_timestamps = FALSE; // did check timestamps
						    // recently
no_check_timestamps = 0;	// Don't check timestamps

#ifdef FEAT_TERMINAL
		// When TRUE skip calling terminal_loop() once.  Used when
		// typing ':' at the more prompt.
skip_term_loop = FALSE;
#endif
#ifdef FEAT_GUI
// use_gvimrc = NULL;	// "-U" cmdline argument
#endif
cterm_normal_fg_color = 0;
cterm_normal_fg_bold = 0;
cterm_normal_bg_color = 0;
#ifdef FEAT_TERMGUICOLORS
cterm_normal_fg_gui_color = INVALCOLOR;
cterm_normal_bg_gui_color = INVALCOLOR;
#endif
#ifdef FEAT_TERMRESPONSE
is_mac_terminal = FALSE;  // recognized Terminal.app
#endif

autocmd_busy = FALSE;	// Is apply_autocmds() busy?
autocmd_no_enter = FALSE; // *Enter autocmds disabled
autocmd_no_leave = FALSE; // *Leave autocmds disabled

modified_was_set = 0;		// did ":set modified"
did_filetype = FALSE;	// FileType event found
keep_filetype = FALSE;	// value for did_filetype when
						// starting to execute
						// autocommands

// Set by the apply_autocmds_group function if the given event is equal to
// EVENT_FILETYPE. Used by the readfile function in order to determine if
// EVENT_BUFREADPOST triggered the EVENT_FILETYPE.
//
// Relying on this value requires one to reset it prior calling
// apply_autocmds_group.
au_did_filetype = FALSE;

// When deleting the current buffer, another one must be loaded.  If we know
// which one is preferred, au_new_curbuf is set to it
au_new_curbuf = (bufref_T) {NULL COMMA 0 COMMA 0};

// When deleting a buffer/window and autocmd_busy is TRUE, do not free the
// buffer/window. but link it in the list starting with
// au_pending_free_buf/ap_pending_free_win, using b_next/w_next.
// Free the buffer/window when autocmd_busy is being set to FALSE.
au_pending_free_buf = NULL;
au_pending_free_win = NULL;

/*
 * Mouse coordinates, set by check_termcode()
 */
mouse_row = 0;
mouse_col = 0;
mouse_past_bottom = FALSE;// mouse below last line
mouse_past_eol = FALSE;	// mouse right of line
mouse_dragging = 0;	// extending Visual area with
						// mouse dragging
#if defined(FEAT_MOUSE_DEC)
/*
 * When the DEC mouse has been pressed but not yet released we enable
 * automatic queries for the mouse position.
 */
WantQueryMouse = FALSE;
#endif

#ifdef FEAT_GUI
// When the window layout is about to be changed, need_mouse_correct is set,
// so that gui_mouse_correct() is called afterwards, to correct the mouse
// pointer when focus-follow-mouse is being used.
need_mouse_correct = FALSE;

// When double clicking, topline must be the same
gui_prev_topline = 0;
# ifdef FEAT_DIFF
gui_prev_topfill = 0;
# endif
#endif

# ifdef FEAT_MOUSESHAPE
drag_status_line = FALSE;	// dragging the status line
postponed_mouseshape = FALSE; // postponed updating the
						    // mouse pointer shape
drag_sep_line = FALSE;	// dragging vert separator
# endif


#ifdef FEAT_DIFF
// Value set from 'diffopt'.
diff_context = 6;		// context for folds
diff_foldcolumn = 2;	// 'foldcolumn' for diff mode
diff_need_scrollbind = FALSE;
#endif

// While redrawing the screen this flag is set.  It means the screen size
// ('lines' and 'rows') must not be changed.
updating_screen = FALSE;

#ifdef FEAT_MENU
// The root of the menu hierarchy.
root_menu = NULL;
/*
 * While defining the system menu, sys_menu is TRUE.  This avoids
 * overruling of menus that the user already defined.
 */
sys_menu = FALSE;
#endif

#ifdef FEAT_GUI
# ifdef FEAT_MENU
// Menu item just selected, set by check_termcode()
current_menu = NULL;

// Set to TRUE after adding/removing menus to ensure they are updated
force_menu_update = FALSE;
# endif
# ifdef FEAT_GUI_TABLINE
// Tab in tab pages line just selected, set by check_termcode()
current_tab = 0;

// Menu entry in tab pages line menu just selected, set by check_termcode()
current_tabmenu = 0;
# endif

// Scrollbar moved and new value, set by check_termcode()
current_scrollbar = 0;
scrollbar_value = 0;

// found "-rv" or "-reverse" in command line args
found_reverse_arg = FALSE;

// "-fn" or "-font" command line argument
font_argument = NULL;

# ifdef FEAT_GUI_GTK
// "-bg" or "-background" command line argument
background_argument = NULL;

// "-fg" or "-foreground" command line argument
foreground_argument = NULL;
# endif

/*
 * While executing external commands or in Ex mode, should not insert GUI
 * events in the input buffer: Set hold_gui_events to non-zero.
 *
 * volatile because it is used in signal handler sig_sysmouse().
 */
hold_gui_events = 0;

/*
 * When resizing the shell is postponed, remember the new size, and call
 * gui_resize_shell() later.
 */
new_pixel_width = 0;
new_pixel_height = 0;

// Window position from ":winpos", to be used when opening the GUI window.
gui_win_x = -1;
gui_win_y = -1;
#endif

#ifdef FEAT_CLIPBOARD

clip_unnamed = 0; // above two values or'ed

clip_autoselect_star = FALSE;
clip_autoselect_plus = FALSE;
clip_autoselectml = FALSE;
clip_html = FALSE;
clip_exclude_prog = NULL;
clip_unnamed_saved = 0;
#endif

/*
 * All regular windows are linked in a list. "firstwin" points to the first
 * entry, "lastwin" to the last entry (can be the same as firstwin) and
 * "curwin" to the currently active window.
 * When switching tabs these swapped with the pointers in "tabpage_T".
 */
firstwin = NULL;		// first window
lastwin = NULL;		// last window
prevwin = NULL;	// previous window
/*
 * When using this macro "break" only breaks out of the inner loop. Use "goto"
 * to break out of the tabpage loop.
 */

curwin = NULL;	// currently active window

aucmd_win = NULL;	// window used in aucmd_prepbuf()
aucmd_win_used = FALSE;	// aucmd_win is being used

#ifdef FEAT_TEXT_PROP
first_popupwin = NULL;		// first global popup window
popup_dragwin = NULL;	// popup window being dragged

// Set to TRUE if there is any visible popup window.
popup_visible = FALSE;

text_prop_frozen = 0;
#endif

/*
 * The window layout is kept in a tree of frames.  topframe points to the top
 * of the tree.
 */
topframe = NULL;	// top of the window frame tree

/*
 * Tab pages are alternative topframes.  "first_tabpage" points to the first
 * one in the list, "curtab" is the current one.
 */
first_tabpage = NULL;
curtab = NULL;
redraw_tabline = FALSE;  // need to redraw tabline

/*
 * All buffers are linked in a list. 'firstbuf' points to the first entry,
 * 'lastbuf' to the last entry and 'curbuf' to the currently active buffer.
 */
firstbuf = NULL;	// first buffer
lastbuf = NULL;	// last buffer
curbuf = NULL;	// currently active buffer

// Flag that is set when switching off 'swapfile'.  It means that all blocks
// are to be loaded into memory.  Shouldn't be global...
mf_dont_release = FALSE;	// don't release blocks

/*
 * List of files being edited (global argument list).  curwin->w_alist points
 * to this when the window is using the global argument list.
 */
max_alist_id = 0;	    // the previous argument list id
arg_had_last = FALSE; // accessed last file in

ru_col = 0;		// column for ruler
#ifdef FEAT_STL_OPT
ru_wid = 0;		// 'rulerfmt' width of ruler when non-zero
#endif
sc_col = 0;		// column for shown command

#ifdef TEMPDIRNAMES
vim_tempdir = NULL; // Name of Vim's own temp dir.
					   // Ends in a slash.
#endif

/*
 * When starting or exiting some things are done differently (e.g. screen
 * updating).
 */
starting = NO_SCREEN;
				// first NO_SCREEN, then NO_BUFFERS and then
				// set to 0 when starting up finished
exiting = FALSE;
				// TRUE when planning to exit Vim.  Might
				// still keep on running if there is a changed
				// buffer.
really_exiting = FALSE;
				// TRUE when we are sure to exit, e.g., after
				// a deadly signal
v_dying = 0; // internal value of v:dying
stdout_isatty = TRUE;	// is stdout a terminal?

#if defined(FEAT_AUTOCHDIR)
test_autochdir = FALSE;
#endif
#if defined(EXITFREE)
entered_free_all_mem = FALSE;
				// TRUE when in or after free_all_mem()
#endif
// volatile because it is used in signal handler deathtrap().
volatile sig_atomic_t full_screen = FALSE;
				// TRUE when doing full-screen output
				// otherwise only writing some messages

restricted = FALSE;
				// TRUE when started as "rvim"
secure = FALSE;
				// non-zero when only "safe" commands are
				// allowed, e.g. when sourcing .exrc or .vimrc
				// in current directory

textlock = 0;
				// non-zero when changing text and jumping to
				// another window or buffer is not allowed

curbuf_lock = 0;
				// non-zero when the current buffer can't be
				// changed.  Used for FileChangedRO.
allbuf_lock = 0;
				// non-zero when no buffer name can be
				// changed, no buffer can be deleted and
				// current directory can't be changed.
				// Used for SwapExists et al.
#ifdef HAVE_SANDBOX
sandbox = 0;
				// Non-zero when evaluating an expression in a
				// "sandbox".  Several things are not allowed
				// then.
#endif

silent_mode = FALSE;
				// set to TRUE when "-s" commandline argument
				// used for ex

pos_T	VIsual;		// start position of active Visual selection
VIsual_active = FALSE;
				// whether Visual mode is active
VIsual_select = FALSE;
				// whether Select mode is active
VIsual_reselect = 0;
				// whether to restart the selection after a
				// Select mode mapping or menu

VIsual_mode = 'v';
				// type of Visual mode

redo_VIsual_busy = FALSE;
				// TRUE when redoing Visual

/*
 * The Visual area is remembered for reselection.
 */
resel_VIsual_mode = NUL;	// 'v', 'V', or Ctrl-V
resel_VIsual_line_count = 0;	// number of lines
resel_VIsual_vcol = 0;		// nr of cols or end col

/*
 * When pasting text with the middle mouse button in visual mode with
 * restart_edit set, remember where it started so we can set Insstart.
 */
where_paste_started = (pos_T) {0, 0};

/*
 * This flag is used to make auto-indent work right on lines where only a
 * <RETURN> or <ESC> is typed. It is set when an auto-indent is done, and
 * reset when any other editing is done on the line. If an <ESC> or <RETURN>
 * is received, and did_ai is TRUE, the line is truncated.
 */
did_ai = FALSE;

/*
 * Column of first char after autoindent.  0 when no autoindent done.  Used
 * when 'backspace' is 0, to avoid backspacing over autoindent.
 */
ai_col = 0;

/*
 * This is a character which will end a start-middle-end comment when typed as
 * the first character on a new line.  It is taken from the last character of
 * the "end" comment leader when the COM_AUTO_END flag is given for that
 * comment end in 'comments'.  It is only valid when did_ai is TRUE.
 */
end_comment_pending = NUL;

/*
 * This flag is set after a ":syncbind" to let the check_scrollbind() function
 * know that it should not attempt to perform scrollbinding due to the scroll
 * that was a result of the ":syncbind." (Otherwise, check_scrollbind() will
 * undo some of the work done by ":syncbind.")  -ralston
 */
did_syncbind = FALSE;

#ifdef FEAT_SMARTINDENT
/*
 * This flag is set when a smart indent has been performed. When the next typed
 * character is a '{' the inserted tab will be deleted again.
 */
did_si = FALSE;

/*
 * This flag is set after an auto indent. If the next typed character is a '}'
 * one indent will be removed.
 */
can_si = FALSE;

/*
 * This flag is set after an "O" command. If the next typed character is a '{'
 * one indent will be removed.
 */
can_si_back = FALSE;
#endif

old_indent = 0;	// for ^^D command in insert mode

saved_cursor = (pos_T) {0, 0, 0};		// w_cursor before formatting text.

/*
 * Stuff for insert mode.
 */
Insstart = (pos_T) {0, 0};		// This is where the latest
					// insert/append mode started.

/* This is where the latest insert/append mode started. In contrast to
 * Insstart, this won't be reset by certain keys and is needed for
 * op_insert(), to detect correctly where inserting by the user started. */
Insstart_orig = (pos_T) {0, 0};

/*
 * Stuff for VREPLACE mode.
 */
orig_line_count = 0;  // Line count when "gR" started
vr_lines_changed = 0; // #Lines changed by "gR" so far

#if defined(FEAT_X11) && defined(FEAT_XCLIPBOARD)
/* argument to SETJMP() for handling X IO errors */
x_jump_env = NULL;
#endif

enc_dbcs = 0;		// One of DBCS_xxx values if
						// DBCS encoding
enc_unicode = 0;	// 2: UCS-2 or UTF-16, 4: UCS-4
enc_utf8 = FALSE;		// UTF-8 encoded Unicode
enc_latin1like = TRUE;	// 'encoding' is latin1 comp.
#if defined(MSWIN) || defined(FEAT_CYGWIN_WIN32_CLIPBOARD)
// Codepage nr of 'encoding'.  Negative means it's not been set yet, zero
// means 'encoding' is not a valid codepage.
enc_codepage = -1;
enc_latin9 = FALSE;	// 'encoding' is latin9
#endif
has_mbyte = 0;		// any multi-byte encoding

// Variables that tell what conversion is used for keyboard input and display
// output.
// input_conv = 0;			// type of input conversion
// output_conv = 0;			// type of output conversion

/*
 * Function pointers, used to quickly get to the right function.  Each has
 * three possible values: latin_ (8-bit), utfc_ or utf_ (utf-8) and dbcs_
 * (DBCS).
 * The value is set in mb_init();
 */
// length of char in bytes, including following composing chars
mb_ptr2len = latin_ptr2len;
// idem, with limit on string length
mb_ptr2len_len = latin_ptr2len_len;
// byte length of char
mb_char2len = latin_char2len;
// convert char to bytes, return the length
mb_char2bytes = latin_char2bytes;
mb_ptr2cells = latin_ptr2cells;
mb_ptr2cells_len = latin_ptr2cells_len;
mb_char2cells = latin_char2cells;
mb_off2cells = latin_off2cells;
mb_ptr2char = latin_ptr2char;
mb_head_off = latin_head_off;



#ifdef FEAT_XIM
# ifdef FEAT_GUI_GTK
xic = NULL;
/*
 * Start and end column of the preedit area in virtual columns from the start
 * of the text line.  When there is no preedit area they are set to MAXCOL.
 * "preedit_end_col" is needed for coloring the preedited string.  Drawing the
 * color between "preedit_start_col" and curpos did not work, because some XIM
 * set the cursor position to the first char of the string.
 */
preedit_start_col = MAXCOL;
preedit_end_col = MAXCOL;

// "xim_changed_while_preediting" is set when changed() can set the 'modified'
// flag even while preediting.
	xim_changed_while_preediting = FALSE;
# else
xic = NULL;
# endif
# ifdef FEAT_GUI
xim_fg_color = INVALCOLOR;
xim_bg_color = INVALCOLOR;
# endif
#endif

#ifdef FEAT_HANGULIN
composing_hangul = 0;
#endif

/*
 * "State" is the main state of Vim.
 * There are other variables that modify the state:
 * "Visual_mode"    When State is NORMAL or INSERT.
 * "finish_op"	    When State is NORMAL, after typing the operator and before
 *		    typing the motion command.
 * "motion_force"   Last motion_force  from do_pending_operator()
 * "debug_mode"	    Debug mode.
 */
State = NORMAL;	// This is the current state of the
					// command interpreter.
#ifdef FEAT_EVAL
debug_mode = FALSE;
#endif

finish_op = FALSE;// TRUE while an operator is pending
opcount = 0;	// count for pending operator
motion_force = 0; // motion force for pending operator

/*
 * Ex mode (Q) state
 */
exmode_active = 0;	// zero, EXMODE_NORMAL or EXMODE_VIM
ex_no_reprint = FALSE; // no need to print after z or p

reg_recording = 0;	// register for recording  or zero
reg_executing = 0;	// register being executed or zero

// Set when a modifyOtherKeys sequence was seen, then simplified mappings will
// no longer be used.
seenModifyOtherKeys = FALSE;

no_mapping = FALSE;	// currently no mapping allowed
no_zero_mapping = 0;	// mapping zero not allowed
allow_keys = FALSE;	// allow key codes when no_mapping
					// is set
no_reduce_keys = FALSE;  // do not apply Ctrl, Shift and Alt
					  // to the key
no_u_sync = 0;		// Don't call u_sync()
#ifdef FEAT_EVAL
u_sync_once = 0;	// Call u_sync() once when evaluating
					// an expression.
#endif

restart_edit = 0;	// call edit when next cmd finished
arrow_used = 0;			// Normally FALSE, set to TRUE after
					// hitting cursor key in insert mode.
					// Used by vgetorpeek() to decide when
					// to call u_sync()
ins_at_eol = FALSE; // put cursor after eol when
					  // restarting edit after CTRL-O

no_abbr = TRUE;	// TRUE when no abbreviations loaded

#ifdef USE_EXE_NAME
exe_name = NULL;		// the name of the executable
#endif

#ifdef USE_ON_FLY_SCROLL
dont_scroll = FALSE;// don't use scrollbars when TRUE
#endif
mapped_ctrl_c = FALSE; // modes where CTRL-C is mapped
ctrl_c_interrupts = TRUE;	// CTRL-C sets got_int

msg_silent = 0;	// don't print messages
emsg_silent = 0;	// don't print error messages
emsg_noredir = 0;	// don't redirect error messages
cmd_silent = FALSE; // don't echo the command line

swap_exists_action = SEA_NONE;
					// For dialog when swap file already
					// exists.
swap_exists_did_quit = FALSE;
					// Selected "quit" at the dialog.

IObuff = NULL;		// sprintf's are done in this buffer,
					// size is IOSIZE
NameBuff = NULL;		// file names are expanded in this
					// buffer, size is MAXPATHL
// When non-zero, postpone redrawing.
RedrawingDisabled = 0;

readonlymode = FALSE; // Set to TRUE for "view"
recoverymode = FALSE; // Set to TRUE for "-r" option

typebuf	= (typebuf_T) {NULL, NULL, 0, 0, 0, 0, 0, 0, 0} ; // typeahead buffer
ex_normal_busy = 0; // recursiveness of ex_normal()
ex_normal_lock = 0; // forbid use of ex_normal()
#ifdef FEAT_EVAL
ignore_script = FALSE;  // ignore script input
#endif
stop_insert_mode = 0;	// for ":stopinsert" and 'insertmode'

KeyTyped = 0;		// TRUE if user typed current char
KeyStuffed = 0;		// TRUE if current char from stuffbuf
#ifdef HAVE_INPUT_METHOD
vgetc_im_active = 0;	// Input Method was active for last
					// character obtained from vgetc()
#endif
maptick = 0;	// tick for each non-mapped char

must_redraw = 0;	    // type of redraw necessary
skip_redraw = FALSE;  // skip redraw once
do_redraw = FALSE;    // extra redraw once
#ifdef FEAT_DIFF
need_diff_redraw = 0; // need to call diff_redraw()
#endif

need_highlight_changed = TRUE;

#define NSCRIPT 15
curscript = 0;	    // index in scriptin[]
scriptout  = NULL;   // stream to write script to
read_cmd_fd = 0;	    // fd to read commands from

// volatile because it is used in signal handler catch_sigint().
got_int = FALSE; // set to TRUE when interrupt
						// signal occurred
#ifdef USE_TERM_CONSOLE
term_console = FALSE; // set to TRUE when console used
#endif
termcap_active = FALSE;	// set by starttermcap()
cur_tmode = TMODE_COOK;	// input terminal mode
bangredo = FALSE;	    // set to TRUE with ! command
searchcmdlen = 0;		    // length of previous search cmd
#ifdef FEAT_SYN_HL
reg_do_extmatch = 0;  // Used when compiling regexp:
					    // REX_SET to allow \z\(...\),
					    // REX_USE to allow \z\1 et al.
reg_extmatch_T *re_extmatch_in = NULL; // Used by vim_regexec():
					    // strings for \z\1...\z\9
reg_extmatch_T *re_extmatch_out = NULL; // Set by vim_regexec()
					    // to store \z\(...\) matches
#endif

did_outofmem_msg = FALSE;
					    // set after out of memory msg
did_swapwrite_msg = FALSE;
					    // set after swap write error msg
undo_off = FALSE;	    // undo switched off for now
global_busy = 0;	    // set when :global is executing
listcmd_busy = FALSE; // set when :argdo, :windo or
					    // :bufdo is executing
need_start_insertmode = FALSE;
					    // start insert mode soon
last_cmdline = NULL; // last command line (for ":)
repeat_cmdline = NULL; // command line for "."
new_last_cmdline = NULL;	// new value for last_cmdline
autocmd_fname = NULL; // fname for <afile> on cmdline
autocmd_fname_full = 0;	     // autocmd_fname is full path
autocmd_bufnr = 0;     // fnum for <abuf> on cmdline
autocmd_match = NULL; // name for <amatch> on cmdline
did_cursorhold = FALSE; // set when CursorHold t'gerd
last_cursormoved = (pos_T) {0, 0, 0} ;	      // for CursorMoved event

postponed_split = 0;  // for CTRL-W CTRL-] command
postponed_split_flags = 0;  // args for win_split()
postponed_split_tab = 0;  // cmdmod.tab
#ifdef FEAT_QUICKFIX
g_do_tagpreview = 0;  // for tag preview commands:
					    // height of preview window
#endif
g_tag_at_cursor = FALSE; // whether the tag command comes
					    // from the command line (0) or was
					    // invoked as a normal command (1)

replace_offset = 0;   // offset for replace_push()

escape_chars = (char_u *)" \t\\\"|";
					    // need backslash in cmd line

keep_help_flag = FALSE; // doing :ta from help file

/*
 * When a string option is NULL (which only happens in out-of-memory
 * situations), it is set to empty_option, to avoid having to check for NULL
 * everywhere.
 */
empty_option = (char_u *)"";

redir_off = FALSE;	// no redirection for a moment
redir_fd = NULL;	// message redirection file
#ifdef FEAT_EVAL
redir_reg = 0;	// message redirection register
redir_vname = 0;	// message redirection variable
redir_execute = 0;	// execute() redirection
#endif

#ifdef FEAT_WILDMENU
save_p_ls = -1;	// Save 'laststatus' setting
save_p_wmh = -1;	// Save 'winminheight' setting
wild_menu_showing = 0;
#endif

homedir = NULL;

// When a window has a local directory, the absolute path of the global
// current directory is stored here (in allocated memory).  If the current
// directory is not a local directory, globaldir is NULL.
globaldir = NULL;

// Characters from 'listchars' option
lcs_eol = '$';
lcs_ext = NUL;
lcs_prec = NUL;
lcs_nbsp = NUL;
lcs_space = NUL;
lcs_tab1 = NUL;
lcs_tab2 = NUL;
lcs_tab3 = NUL;
lcs_trail = NUL;
#ifdef FEAT_CONCEAL
lcs_conceal = ' ';
#endif

// Characters from 'fillchars' option
fill_stl = ' ';
fill_stlnc = ' ';
fill_vert = ' ';
fill_fold = '-';
fill_diff = '-';

#ifdef FEAT_FOLDING
disable_fold_update = 0;
#endif

// Whether 'keymodel' contains "stopsel" and "startsel".
km_stopsel = FALSE;
km_startsel = FALSE;

#ifdef FEAT_CMDWIN
cedit_key = -1;	// key value of 'cedit' option
cmdwin_type = 0;	// type of cmdline window or 0
cmdwin_result = 0; // result of cmdline window or 0
#endif

// no_lines_msg	= N_("--No lines in buffer--");

/*
 * When ":global" is used to number of substitutions and changed lines is
 * accumulated until it's finished.
 * Also used for ":spellrepall".
 */
sub_nsubs = 0;	// total number of substitutions
sub_nlines = 0;	// total number of lines changed

#if defined(FEAT_TITLE) && defined(FEAT_STL_OPT)
// whether titlestring and iconstring contains statusline syntax
stl_syntax = 0;
#endif

#ifdef FEAT_SEARCH_EXTRA
// don't use 'hlsearch' temporarily
no_hlsearch = FALSE;
#endif

#if defined(FEAT_BEVAL) && !defined(NO_X11_INCLUDES)
balloonEval = NULL;
balloonEvalForTerm = FALSE;
# if defined(FEAT_NETBEANS_INTG)
bevalServers = 0;
# endif
#endif

#if (defined(FEAT_PRINTER) && defined(FEAT_STL_OPT)) \
	    || defined(FEAT_GUI_TABLINE)
// Page number used for %N in 'pageheader' and 'guitablabel'.
printer_page_num = 0;
#endif

#ifdef FEAT_XCLIPBOARD
// xterm display name
xterm_display = NULL;

// whether xterm_display was allocated, when FALSE it points into argv[]
xterm_display_allocated = FALSE;

// xterm display pointer
xterm_dpy = NULL;
#endif
#if defined(FEAT_XCLIPBOARD) || defined(FEAT_GUI_X11)
app_context = (XtAppContext)NULL;
#endif

#ifdef FEAT_GUI_GTK
gtk_socket_id = 0;
echo_wid_arg = FALSE;	// --echo-wid argument
#endif

#ifdef FEAT_GUI_MSWIN
/*
 * The value of the --windowid argument.
 * For embedding gvim inside another application.
 */
win_socket_id = 0;
#endif

#if defined(FEAT_CLIENTSERVER) || defined(FEAT_EVAL)
typebuf_was_filled = FALSE; // received text from client
						  // or from feedkeys()
#endif

#ifdef FEAT_CLIENTSERVER
serverName = NULL;	// name of the server
# ifdef FEAT_X11
commWindow = None;
clientWindow = None;
commProperty = None;
serverDelayedStartName = NULL;
# else
clientWindow = 0;
# endif
#endif

#if defined(UNIX) || defined(VMS)
term_is_xterm = FALSE;	// xterm-like 'term'
#endif

#ifdef BACKSLASH_IN_FILENAME
psepc = '\\';	// normal path separator character
psepcN = '/';	// abnormal path separator character
/* normal path separator string */
pseps[2] = (char) {'\\' COMMA 0};
#endif

// Set to TRUE when an operator is being executed with virtual editing, MAYBE
// when no operator is being executed, FALSE otherwise.
virtual_op = MAYBE;

#ifdef FEAT_SYN_HL
// Display tick, incremented for each call to update_screen()
display_tick = 0;
#endif

#ifdef FEAT_SPELL
// Line in which spell checking wasn't highlighted because it touched the
// cursor position in Insert mode.
spell_redraw_lnum = 0;
#endif

#ifdef FEAT_CONCEAL
// Set when the cursor line needs to be redrawn.
need_cursor_line_redraw = FALSE;
#endif

#ifdef USE_MCH_ERRMSG
// Grow array to collect error messages in until they can be displayed.
error_ga = (garray_T) {0, 0, 0, 0, NULL} ;
#endif

#ifdef FEAT_NETBEANS_INTG
netbeansArg = NULL;	// the -nb[:host:port:passwd] arg
netbeansFireChanges = 1; // send buffer changes if != 0
netbeansForcedQuit = 0;// don't write modified files
netbeansReadFile = 1;	// OK to read from disk if != 0
netbeansSuppressNoLines = 0; // skip "No lines in buffer"
#endif

#ifdef FEAT_GUI_MAC
disallow_gui	= FALSE;
#endif

/*
 * Comms. with the session manager (XSMP)
 */
#ifdef USE_XSMP
xsmp_icefd = -1;   // The actual connection
#endif

// For undo we need to know the lowest time possible.
starttime = 0;

#ifdef STARTUPTIME
time_fd = NULL;  // where to write startup timing
#endif

/*
 * Some compilers warn for not using a return value, but in some situations we
 * can't do anything useful with the value.  Assign to this variable to avoid
 * the warning.
 */
vim_ignored = 0;
vim_ignoredp = 0;

#ifdef FEAT_EVAL
// set by alloc_fail(): ID
alloc_fail_id = (alloc_id_T) aid_none;
// set by alloc_fail(), when zero alloc() returns NULL
alloc_fail_countdown = -1;
// set by alloc_fail(), number of times alloc() returns NULL
alloc_fail_repeat = 0;

// flags set by test_override()
disable_char_avail_for_testing = FALSE;
disable_redraw_for_testing = FALSE;
ignore_redraw_flag_for_testing = FALSE;
nfa_fail_for_testing = FALSE;
no_query_mouse_for_testing = FALSE;

in_free_unref_items = FALSE;
#endif

#ifdef FEAT_TIMERS
did_add_timer = FALSE;
timer_busy = 0;   // when timer is inside vgetc() then > 0
#endif

#ifdef FEAT_BEVAL_TERM
bevalexpr_due_set = FALSE;
bevalexpr_due = 0;
#endif

#ifdef FEAT_EVAL
time_T time_for_testing = 0;

// Abort conversion to string after a recursion error.
did_echo_string_emsg = FALSE;

// Used for checking if local variables or arguments used in a lambda.
eval_lavars_used = NULL;
#endif

#ifdef MSWIN
ctrl_break_was_pressed = FALSE;
g_hinst = NULL;
#endif

#if defined(FEAT_JOB_CHANNEL)
did_repeated_msg = 0;
#endif
