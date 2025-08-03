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

/*
 * Number of Rows and Columns in the screen.
 * Must be long to be able to use them as options in option.c.
 * Note: Use screen_Rows and screen_Columns to access items in ScreenLines[].
 * They may have different values when the screen wasn't (re)allocated yet
 * after setting Rows or Columns (e.g., when starting up).
 */
Rows    // nr of rows in the screen
# if defined(MSWIN)
			    = 25L
# else
			    = 24L
# endif
			    ;
Columns INIT(= 80);	// nr of columns in the screen

/*
 * The characters that are currently on the screen are kept in ScreenLines[].
 * It is a single block of characters, the size of the screen plus one line.
 * The attributes for those characters are kept in ScreenAttrs[].
 *
 * "LineOffset[n]" is the offset from ScreenLines[] for the start of line 'n'.
 * The same value is used for ScreenLinesUC[] and ScreenAttrs[].
 *
 * Note: before the screen is initialized and when out of memory these can be
 * NULL.
 */
ScreenLines INIT(= NULL);
ScreenAttrs INIT(= NULL);
LineOffset INIT(= NULL);
LineWraps INIT(= NULL);	// line wraps to next line

/*
 * When using Unicode characters (in UTF-8 encoding) the character in
 * ScreenLinesUC[] contains the Unicode for the character at this position, or
 * NUL when the character in ScreenLines[] is to be used (ASCII char).
 * The composing characters are to be drawn on top of the original character.
 * ScreenLinesC[0][off] is only to be used when ScreenLinesUC[off] != 0.
 * Note: These three are only allocated when enc_utf8 is set!
 */
ScreenLinesUC INIT(= NULL);	// decoded UTF-8 characters

Screen_mco INIT(= 0);		// value of p_mco used when
						// allocating ScreenLinesC[]

// Only used for euc-jp: Second byte of a character that starts with 0x8e.
// These are single-width.
ScreenLines2 INIT(= NULL);

/*
 * Buffer for one screen line (characters and attributes).
 */
current_ScreenLine INIT(= NULL);

/*
 * Last known cursor position.
 * Positioning the cursor is reduced by remembering the last position.
 * Mostly used by windgoto() and screen_char().
 */
screen_cur_row INIT(= 0);
screen_cur_col INIT(= 0);

#ifdef FEAT_SEARCH_EXTRA
// used for 'hlsearch' highlight matching
// EXTERN match_T	screen_search_hl;

// last lnum where CurSearch was displayed
search_hl_has_cursor_lnum INIT(= 0);

// don't use 'hlsearch' temporarily
no_hlsearch INIT(= FALSE);
#endif

#ifdef FEAT_FOLDING
// EXTERN foldinfo_T win_foldinfo;	// info for 'foldcolumn'
#endif

// Flag that is set when drawing for a callback, not from the main command
// loop.
redrawing_for_callback INIT(= 0);

/*
 * Indexes for tab page line:
 *	N > 0 for label of tab page N
 *	N == 0 for no label
 *	N < 0 for closing tab page -N
 *	N == -999 for closing current tab page
 */
TabPageIdxs INIT(= NULL);

#ifdef FEAT_PROP_POPUP
// Array with size Rows x Columns containing zindex of popups.
popup_mask INIT(= NULL);
popup_mask_next INIT(= NULL);
// Array with flags for transparent cells of current popup.
popup_transparent INIT(= NULL);

// Flag set to TRUE when popup_mask needs to be updated.
popup_mask_refresh INIT(= TRUE);

// Tab that was used to fill popup_mask.
popup_mask_tab INIT(= NULL);

// Zindex in for screen_char(): if lower than the value in "popup_mask"
// drawing the character is skipped.
screen_zindex INIT(= 0);
#endif

screen_Rows INIT(= 0);	    // actual size of ScreenLines[]
screen_Columns INIT(= 0);   // actual size of ScreenLines[]

/*
 * When vgetc() is called, it sets mod_mask to the set of modifiers that are
 * held down based on the MOD_MASK_* symbols that are read first.
 */
mod_mask INIT(= 0);		// current key modifiers

// The value of "mod_mask" and the unomdified character before calling
// merge_modifyOtherKeys().
vgetc_mod_mask INIT(= 0);
vgetc_char INIT(= 0);

/*
 * Cmdline_row is the row where the command line starts, just below the
 * last window.
 * When the cmdline gets longer than the available space the screen gets
 * scrolled up. After a CTRL-D (show matches), after hitting ':' after
 * "hit return", and for the :global command, the command line is
 * temporarily moved.  The old position is restored with the next call to
 * update_screen().
 */
cmdline_row INIT(= 0);

redraw_cmdline INIT(= FALSE);	// cmdline must be redrawn
redraw_mode INIT(= FALSE);	// mode must be redrawn
clear_cmdline INIT(= FALSE);	// cmdline must be cleared
mode_displayed INIT(= FALSE);	// mode is being displayed
no_win_do_lines_ins INIT(= FALSE); // don't insert lines
#if defined(FEAT_CRYPT) || defined(FEAT_EVAL)
cmdline_star INIT(= FALSE);	// cmdline is crypted
#endif

exec_from_reg INIT(= FALSE);	// executing register

screen_cleared INIT(= FALSE);	// screen has been cleared
/*
 * When '$' is included in 'cpoptions' option set:
 * When a change command is given that deletes only part of a line, a dollar
 * is put at the end of the changed text. dollar_vcol is set to the virtual
 * column of this '$'.  -1 is used to indicate no $ is being displayed.
 */
dollar_vcol INIT(= -1);

/*
 * Variables for Insert mode completion.
 */

edit_submode INIT(= NULL); // msg for CTRL-X submode
edit_submode_pre INIT(= NULL); // prepended to edit_submode
edit_submode_extra INIT(= NULL);// appended to edit_submode
edit_submode_highl INIT(= 0);	// highl. method for extra info

/*
 * Functions for putting characters in the command line,
 * while keeping ScreenLines[] updated.
 */
#ifdef FEAT_RIGHTLEFT
cmdmsg_rl INIT(= FALSE);    // cmdline is drawn right to left
#endif
msg_col = 0;
msg_row = 0;
msg_scrolled = 0;	// Number of screen lines that windows have
				// scrolled because of printing messages.
msg_scrolled_ign INIT(= FALSE);
				// when TRUE don't set need_wait_return in
				// msg_puts_attr() when msg_scrolled is
				// non-zero

keep_msg INIT(= NULL);	    // msg to be shown after redraw
keep_msg_attr INIT(= 0);    // highlight attr for keep_msg
keep_msg_more INIT(= FALSE); // keep_msg was set by msgmore()
need_fileinfo INIT(= FALSE);// do fileinfo() after redraw
msg_scroll INIT(= FALSE);   // msg_start() will scroll
msg_didout INIT(= FALSE);   // msg_outstr() was used in line
msg_didany INIT(= FALSE);   // msg_outstr() was used at all
msg_nowait INIT(= FALSE);   // don't wait for this msg
emsg_off INIT(= 0);	    // don't display errors for now,
					    // unless 'debug' is set.
info_message INIT(= FALSE); // printing informative message
msg_hist_off INIT(= FALSE); // don't add messages to history
#ifdef FEAT_EVAL
need_clr_eos INIT(= FALSE); // need to clear text before
				    // displaying a message.
emsg_skip INIT(= 0);	    // don't display errors for
				    // expression that is skipped
emsg_severe INIT(= FALSE);  // use message of next of several
				    // emsg() calls for throw
// used by assert_fails()
emsg_assert_fails_msg INIT(= NULL);
emsg_assert_fails_lnum INIT(= 0);
emsg_assert_fails_context INIT(= NULL);

did_endif INIT(= FALSE);    // just had ":endif"
#endif
did_emsg = 0;		    // set by emsg() when the message
					    // is displayed or thrown
#ifdef FEAT_EVAL
did_emsg_silent INIT(= 0);  // incremented by emsg() when
					    // emsg_silent was set and did_emsg
					    // is not incremented
did_emsg_def = 0;		    // set by emsg() when emsg_silent
					    // is set before calling a function
did_emsg_cumul = 0;		    // cumulative did_emsg, increased
					    // when did_emsg is reset.
called_vim_beep = 0;	    // set if vim_beep() is called
uncaught_emsg = 0;	    // number of times emsg() was
					    // called and did show a message
#endif
did_emsg_syntax = 0;	    // did_emsg set because of a
					    // syntax error
called_emsg = 0;		    // always incremented by emsg()
ex_exitval INIT(= 0);	    // exit value for ex mode
emsg_on_display INIT(= FALSE);	// there is an error message
rc_did_emsg INIT(= FALSE);  // vim_regcomp() called emsg()

no_wait_return INIT(= 0);   // don't wait for return for now
need_wait_return INIT(= 0); // need to wait for return later
did_wait_return INIT(= FALSE);	// wait_return() was used and
						// nothing written since then
need_maketitle INIT(= TRUE); // call maketitle() soon

quit_more INIT(= FALSE);    // 'q' hit at "--more--" msg
#if defined(UNIX) || defined(VMS) || defined(MACOS_X)
newline_on_exit INIT(= FALSE);	// did msg in altern. screen
intr_char INIT(= 0);	    // extra interrupt character
#endif
#if (defined(UNIX) || defined(VMS)) && defined(FEAT_X11)
x_no_connect INIT(= FALSE); // don't connect to X server
# if defined(FEAT_CLIENTSERVER)
x_force_connect INIT(= FALSE);	// Do connect to X server.
						// Overrules x_no_connect and
						// "exclude" in 'clipboard'.
# endif
#endif
ex_keep_indent INIT(= FALSE); // getexmodeline(): keep indent
vgetc_busy INIT(= 0);	      // when inside vgetc() then > 0

didset_vim INIT(= FALSE);	    // did set $VIM ourselves
didset_vimruntime INIT(= FALSE);    // idem for $VIMRUNTIME

/*
 * Lines left before a "more" message.	Ex mode needs to be able to reset this
 * after you type something.
 */
lines_left INIT(= -1);	    // lines left for listing
msg_no_more INIT(= FALSE);  // don't use more prompt, truncate
					    // messages

/*
 * Stack of execution contexts.  Each entry is an estack_T.
 * Current context is at ga_len - 1.
 */
// exestack INIT5(0, 0, sizeof(estack_T), 50, NULL);
exestack = (garray_T) {0, 0, sizeof(estack_T), 50, NULL};

// Script CTX being sourced or was sourced to define the current function.
current_sctx = (sctx_T) {0, 0, 0, 0}; 
// #ifdef FEAT_EVAL
//     INIT4(0, 0, 0, 0);
// #else
//     INIT(= {0});
// #endif

#ifdef FEAT_EVAL
// whether inside compile_def_function()
estack_compiling INIT(= FALSE);

ex_nesting_level INIT(= 0);	// nesting level
debug_break_level INIT(= -1);	// break below this level
debug_did_msg INIT(= FALSE);	// did "debug mode" message
debug_tick INIT(= 0);		// breakpoint change count
debug_backtrace_level INIT(= 0); // breakpoint backtrace level
# ifdef FEAT_PROFILE
do_profiling INIT(= PROF_NONE);	// PROF_ values
# endif
// script_items INIT5(0, 0, sizeof(scriptitem_T *), 20, NULL);
script_items = (garray_T) {0, 0, sizeof(scriptitem_T *), 20, NULL};

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
did_throw INIT(= FALSE);

/*
 * need_rethrow: set to TRUE when a throw that cannot be handled in do_cmdline()
 * must be propagated to the cstack of the previously called do_cmdline().
 */
need_rethrow INIT(= FALSE);

/*
 * check_cstack: set to TRUE when a ":finish" or ":return" that cannot be
 * handled in do_cmdline() must be propagated to the cstack of the previously
 * called do_cmdline().
 */
check_cstack INIT(= FALSE);

/*
 * Number of nested try conditionals (across function calls and ":source"
 * commands).
 */
trylevel INIT(= 0);

/*
 * When "force_abort" is TRUE, always skip commands after an error message,
 * even after the outermost ":endif", ":endwhile" or ":endfor" or for a
 * function without the "abort" flag.  It is set to TRUE when "trylevel" is
 * non-zero (and ":silent!" was not used) or an exception is being thrown at
 * the time an error is detected.  It is set to FALSE when "trylevel" gets
 * zero again and there was no error or interrupt or throw.
 */
force_abort INIT(= FALSE);

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
msg_list INIT(= NULL);

/*
 * suppress_errthrow: When TRUE, don't convert an error to an exception.  Used
 * when displaying the interrupt message or reporting an exception that is still
 * uncaught at the top level (which has already been discarded then).  Also used
 * for the error message when no exception can be thrown.
 */
suppress_errthrow INIT(= FALSE);

/*
 * The stack of all caught and not finished exceptions.  The exception on the
 * top of the stack is the one got by evaluation of v:exception.  The complete
 * stack of all caught and pending exceptions is embedded in the various
 * cstacks; the pending exceptions, however, are not on the caught stack.
 */
caught_stack INIT(= NULL);

/*
 * Garbage collection can only take place when we are sure there are no Lists
 * or Dictionaries being used internally.  This is flagged with
 * "may_garbage_collect" when we are at the toplevel.
 * "want_garbage_collect" is set by the garbagecollect() function, which means
 * we do garbage collection before waiting for a char at the toplevel.
 * "garbage_collect_at_exit" indicates garbagecollect(1) was called.
 */
may_garbage_collect INIT(= FALSE);
want_garbage_collect INIT(= FALSE);
garbage_collect_at_exit INIT(= FALSE);


// Commonly used types.
// "unknown" is used for when the type is really unknown, e.g. global
// variables.  Also for when a function may or may not return something.
// t_unknown INIT6(VAR_UNKNOWN, 0, 0, TTFLAG_STATIC, NULL, NULL);
t_unknown = (type_T) {VAR_UNKNOWN, 0, 0, TTFLAG_STATIC, NULL, NULL};

// "any" is used for when the type is mixed.  Excludes "void".
t_any = (type_T) {VAR_ANY, 0, 0, TTFLAG_STATIC, NULL, NULL};

// "void" is used for a function not returning anything.
t_void = (type_T) {VAR_VOID, 0, 0, TTFLAG_STATIC, NULL, NULL};

t_bool = (type_T) {VAR_BOOL, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_null = (type_T) {VAR_SPECIAL, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_none = (type_T) {VAR_SPECIAL, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_number = (type_T) {VAR_NUMBER, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_number_bool = (type_T) {VAR_NUMBER, 0, 0, TTFLAG_STATIC|TTFLAG_BOOL_OK, NULL, NULL};
t_float = (type_T) {VAR_FLOAT, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_string = (type_T) {VAR_STRING, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_blob = (type_T) {VAR_BLOB, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_blob_null = (type_T) {VAR_BLOB, 0, 0, TTFLAG_STATIC, &t_void, NULL};
t_job = (type_T) {VAR_JOB, 0, 0, TTFLAG_STATIC, NULL, NULL};
t_channel = (type_T) {VAR_CHANNEL, 0, 0, TTFLAG_STATIC, NULL, NULL};

// Special value used for @#.
t_number_or_string = (type_T) {VAR_STRING, 0, 0, TTFLAG_STATIC, NULL, NULL};

t_func_unknown = (type_T) {VAR_FUNC, -1, -1, TTFLAG_STATIC, &t_unknown, NULL};
t_func_void = (type_T) {VAR_FUNC, -1, 0, TTFLAG_STATIC, &t_void, NULL};
t_func_any = (type_T) {VAR_FUNC, -1, 0, TTFLAG_STATIC, &t_any, NULL};
t_func_number = (type_T) {VAR_FUNC, -1, 0, TTFLAG_STATIC, &t_number, NULL};
t_func_string = (type_T) {VAR_FUNC, -1, 0, TTFLAG_STATIC, &t_string, NULL};
t_func_bool = (type_T) {VAR_FUNC, -1, 0, TTFLAG_STATIC, &t_bool, NULL};
t_func_0_void = (type_T) {VAR_FUNC, 0, 0, TTFLAG_STATIC, &t_void, NULL};
t_func_0_any = (type_T) {VAR_FUNC, 0, 0, TTFLAG_STATIC, &t_any, NULL};
t_func_0_number = (type_T) {VAR_FUNC, 0, 0, TTFLAG_STATIC, &t_number, NULL};
t_func_0_string = (type_T) {VAR_FUNC, 0, 0, TTFLAG_STATIC, &t_string, NULL};

t_list_any = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_any, NULL};
t_dict_any = (type_T) {VAR_DICT, 0, 0, TTFLAG_STATIC, &t_any, NULL};
t_list_empty = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_unknown, NULL};
t_dict_empty = (type_T) {VAR_DICT, 0, 0, TTFLAG_STATIC, &t_unknown, NULL};

t_list_bool = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_bool, NULL};
t_list_number = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_number, NULL};
t_list_string = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_string, NULL};
t_list_job = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_job, NULL};
t_list_dict_any = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_dict_any, NULL};
t_list_list_any = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_list_any, NULL};
t_list_list_string = (type_T) {VAR_LIST, 0, 0, TTFLAG_STATIC, &t_list_string, NULL};

t_dict_bool = (type_T) {VAR_DICT, 0, 0, TTFLAG_STATIC, &t_bool, NULL};
t_dict_number = (type_T) {VAR_DICT, 0, 0, TTFLAG_STATIC, &t_number, NULL};
t_dict_string = (type_T) {VAR_DICT, 0, 0, TTFLAG_STATIC, &t_string, NULL};
#endif

#ifdef FEAT_EVAL
did_source_packages INIT(= FALSE);
#endif

// Magic number used for hashitem "hi_key" value indicating a deleted item.
// Only the address is used.
hash_removed = NUL;


scroll_region INIT(= FALSE); // term supports scroll region
t_colors INIT(= 0);	    // int value of T_CCO

// Flags to indicate an additional string for highlight name completion.
include_none INIT(= 0);	// when 1 include "None"
include_default INIT(= 0);	// when 1 include "default"
include_link INIT(= 0);	// when 2 include "link" and "clear"

/*
 * When highlight_match is TRUE, highlight a match, starting at the cursor
 * position.  Search_match_lines is the number of lines after the match (0 for
 * a match within one line), search_match_endcol the column number of the
 * character just after the match in the last line.
 */
highlight_match INIT(= FALSE);	// show search match pos
search_match_lines = 0;		// lines of of matched string
search_match_endcol = 0;		// col nr of match end
#ifdef FEAT_SEARCH_EXTRA
search_first_line INIT(= 0);	  // for :{FIRST},{last}s/pat
search_last_line INIT(= MAXLNUM); // for :{first},{LAST}s/pat
#endif

no_smartcase INIT(= FALSE);	// don't use 'smartcase' once

need_check_timestamps INIT(= FALSE); // need to check file
						     // timestamps asap
did_check_timestamps INIT(= FALSE); // did check timestamps
						    // recently
no_check_timestamps INIT(= 0);	// Don't check timestamps

#ifdef FEAT_TERMINAL
		// When TRUE skip calling terminal_loop() once.  Used when
		// typing ':' at the more prompt.
skip_term_loop INIT(= FALSE);
#endif
#ifdef FEAT_GUI
// use_gvimrc INIT(= NULL);	// "-U" cmdline argument
#endif
cterm_normal_fg_color INIT(= 0);
cterm_normal_fg_bold INIT(= 0);
cterm_normal_bg_color INIT(= 0);
#ifdef FEAT_TERMGUICOLORS
cterm_normal_fg_gui_color INIT(= INVALCOLOR);
cterm_normal_bg_gui_color INIT(= INVALCOLOR);
cterm_normal_ul_gui_color INIT(= INVALCOLOR);
#endif
#ifdef FEAT_TERMRESPONSE
is_mac_terminal INIT(= FALSE);  // recognized Terminal.app
#endif

autocmd_busy INIT(= FALSE);	// Is apply_autocmds() busy?
autocmd_no_enter INIT(= FALSE); // *Enter autocmds disabled
autocmd_no_leave INIT(= FALSE); // *Leave autocmds disabled

modified_was_set = 0;		// did ":set modified"
did_filetype INIT(= FALSE);	// FileType event found
keep_filetype INIT(= FALSE);	// value for did_filetype when
						// starting to execute
						// autocommands

// Set by the apply_autocmds_group function if the given event is equal to
// EVENT_FILETYPE. Used by the readfile function in order to determine if
// EVENT_BUFREADPOST triggered the EVENT_FILETYPE.
//
// Relying on this value requires one to reset it prior calling
// apply_autocmds_group.
au_did_filetype INIT(= FALSE);

// When deleting the current buffer, another one must be loaded.  If we know
// which one is preferred, au_new_curbuf is set to it
au_new_curbuf = (bufref_T) {NULL, 0, 0};

// When deleting a buffer/window and autocmd_busy is TRUE, do not free the
// buffer/window. but link it in the list starting with
// au_pending_free_buf/ap_pending_free_win, using b_next/w_next.
// Free the buffer/window when autocmd_busy is being set to FALSE.
au_pending_free_buf INIT(= NULL);
au_pending_free_win INIT(= NULL);

/*
 * Mouse coordinates, set by check_termcode()
 */
mouse_row = 0;
mouse_col = 0;
mouse_past_bottom INIT(= FALSE);// mouse below last line
mouse_past_eol INIT(= FALSE);	// mouse right of line
mouse_dragging INIT(= 0);	// extending Visual area with
						// mouse dragging
#if defined(FEAT_MOUSE_DEC)
/*
 * When the DEC mouse has been pressed but not yet released we enable
 * automatic queries for the mouse position.
 */
WantQueryMouse INIT(= FALSE);
#endif

#ifdef FEAT_GUI
// When the window layout is about to be changed, need_mouse_correct is set,
// so that gui_mouse_correct() is called afterwards, to correct the mouse
// pointer when focus-follow-mouse is being used.
need_mouse_correct INIT(= FALSE);

// When double clicking, topline must be the same
gui_prev_topline INIT(= 0);
# ifdef FEAT_DIFF
gui_prev_topfill INIT(= 0);
# endif
#endif

# ifdef FEAT_MOUSESHAPE
drag_status_line INIT(= FALSE);	// dragging the status line
postponed_mouseshape INIT(= FALSE); // postponed updating the
						    // mouse pointer shape
drag_sep_line INIT(= FALSE);	// dragging vert separator
# endif


#ifdef FEAT_DIFF
// Value set from 'diffopt'.
diff_context INIT(= 6);		// context for folds
diff_foldcolumn INIT(= 2);	// 'foldcolumn' for diff mode
diff_need_scrollbind INIT(= FALSE);
#endif

// While redrawing the screen this flag is set.  It means the screen size
// ('lines' and 'rows') must not be changed.
updating_screen INIT(= FALSE);

#ifdef MESSAGE_QUEUE
// While closing windows or buffers messages should not be handled to avoid
// using invalid windows or buffers.
dont_parse_messages INIT(= FALSE);
#endif

#ifdef FEAT_MENU
// The root of the menu hierarchy.
root_menu INIT(= NULL);
/*
 * While defining the system menu, sys_menu is TRUE.  This avoids
 * overruling of menus that the user already defined.
 */
sys_menu INIT(= FALSE);
#endif

#ifdef FEAT_GUI
# ifdef FEAT_MENU
// Menu item just selected, set by check_termcode()
current_menu INIT(= NULL);

// Set to TRUE after adding/removing menus to ensure they are updated
force_menu_update INIT(= FALSE);
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
found_reverse_arg INIT(= FALSE);

// "-fn" or "-font" command line argument
font_argument INIT(= NULL);

# ifdef FEAT_GUI_GTK
// "-bg" or "-background" command line argument
background_argument INIT(= NULL);

// "-fg" or "-foreground" command line argument
foreground_argument INIT(= NULL);
# endif

/*
 * While executing external commands or in Ex mode, should not insert GUI
 * events in the input buffer: Set hold_gui_events to non-zero.
 *
 * volatile because it is used in signal handler sig_sysmouse().
 */
hold_gui_events INIT(= 0);

/*
 * When resizing the shell is postponed, remember the new size, and call
 * gui_resize_shell() later.
 */
new_pixel_width INIT(= 0);
new_pixel_height INIT(= 0);

// Window position from ":winpos", to be used when opening the GUI window.
gui_win_x INIT(= -1);
gui_win_y INIT(= -1);
#endif

#ifdef FEAT_CLIPBOARD

clip_unnamed INIT(= 0); // above two values or'ed

clip_autoselect_star INIT(= FALSE);
clip_autoselect_plus INIT(= FALSE);
clip_autoselectml INIT(= FALSE);
clip_html INIT(= FALSE);
clip_exclude_prog INIT(= NULL);
clip_unnamed_saved INIT(= 0);
#endif

/*
 * All regular windows are linked in a list. "firstwin" points to the first
 * entry, "lastwin" to the last entry (can be the same as firstwin) and
 * "curwin" to the currently active window.
 * When switching tabs these swapped with the pointers in "tabpage_T".
 */
firstwin = NULL;		// first window
lastwin = NULL;		// last window
prevwin INIT(= NULL);	// previous window
/*
 * When using this macro "break" only breaks out of the inner loop. Use "goto"
 * to break out of the tabpage loop.
 */


curwin = NULL;	// currently active window

aucmd_win = NULL;	// window used in aucmd_prepbuf()
aucmd_win_used  INIT(= FALSE);	// aucmd_win is being used

#ifdef FEAT_PROP_POPUP
first_popupwin = NULL;		// first global popup window
popup_dragwin INIT(= NULL);	// popup window being dragged

// Set to TRUE if there is any visible popup window.
popup_visible INIT(= FALSE);

// Set to TRUE if a visible popup window may use a MOUSE_MOVE event
popup_uses_mouse_move INIT(= FALSE);

text_prop_frozen INIT(= 0);
#endif

// When set the popup menu will redraw soon using the pum_win_ values. Do not
// draw over the poup menu area to avoid flicker.
pum_will_redraw INIT(= FALSE);

/*
 * The window layout is kept in a tree of frames.  topframe points to the top
 * of the tree.
 */
topframe = NULL;	// top of the window frame tree

/*
 * Tab pages are alternative topframes.  "first_tabpage" points to the first
 * one in the list, "curtab" is the current one. "lastused_tabpage" is the
 * last used one.
 */
first_tabpage = NULL;
curtab = NULL;
lastused_tabpage = NULL;
redraw_tabline INIT(= FALSE);  // need to redraw tabline

/*
 * All buffers are linked in a list. 'firstbuf' points to the first entry,
 * 'lastbuf' to the last entry and 'curbuf' to the currently active buffer.
 */
firstbuf INIT(= NULL);	// first buffer
lastbuf INIT(= NULL);	// last buffer
curbuf INIT(= NULL);	// currently active buffer

// Flag that is set when switching off 'swapfile'.  It means that all blocks
// are to be loaded into memory.  Shouldn't be global...
mf_dont_release INIT(= FALSE);	// don't release blocks

/*
 * List of files being edited (global argument list).  curwin->w_alist points
 * to this when the window is using the global argument list.
 */
// EXTERN alist_T	global_alist;		    // global argument list
max_alist_id INIT(= 0);	    // the previous argument list id
arg_had_last INIT(= FALSE); // accessed last file in
					    // global_alist

ru_col = 0;		// column for ruler
#ifdef FEAT_STL_OPT
ru_wid = 0;		// 'rulerfmt' width of ruler when non-zero
#endif
sc_col = 0;		// column for shown command

#ifdef TEMPDIRNAMES
vim_tempdir INIT(= NULL); // Name of Vim's own temp dir.
					   // Ends in a slash.
#endif

/*
 * When starting or exiting some things are done differently (e.g. screen
 * updating).
 */
starting INIT(= NO_SCREEN);
				// first NO_SCREEN, then NO_BUFFERS and then
				// set to 0 when starting up finished
exiting INIT(= FALSE);
				// TRUE when planning to exit Vim.  Might
				// still keep on running if there is a changed
				// buffer.
really_exiting INIT(= FALSE);
				// TRUE when we are sure to exit, e.g., after
				// a deadly signal
v_dying INIT(= 0); // internal value of v:dying
stdout_isatty INIT(= TRUE);	// is stdout a terminal?

#if defined(FEAT_AUTOCHDIR)
test_autochdir INIT(= FALSE);
#endif
last_chdir_reason INIT(= NULL);
#if defined(EXITFREE)
entered_free_all_mem INIT(= FALSE);
				// TRUE when in or after free_all_mem()
#endif
// volatile because it is used in signal handler deathtrap().
full_screen INIT(= FALSE);
				// TRUE when doing full-screen output
				// otherwise only writing some messages

restricted INIT(= FALSE);
				// TRUE when started as "rvim"
secure INIT(= FALSE);
				// non-zero when only "safe" commands are
				// allowed, e.g. when sourcing .exrc or .vimrc
				// in current directory

textlock INIT(= 0);
				// non-zero when changing text and jumping to
				// another window or editing another buffer is
				// not allowed

curbuf_lock INIT(= 0);
				// non-zero when the current buffer can't be
				// changed.  Used for FileChangedRO.
allbuf_lock INIT(= 0);
				// non-zero when no buffer name can be
				// changed, no buffer can be deleted and
				// current directory can't be changed.
				// Used for SwapExists et al.
#ifdef HAVE_SANDBOX
sandbox INIT(= 0);
				// Non-zero when evaluating an expression in a
				// "sandbox".  Several things are not allowed
				// then.
#endif

silent_mode INIT(= FALSE);
				// set to TRUE when "-s" commandline argument
				// used for ex

// pos_T	VIsual;		// start position of active Visual selection
VIsual_active INIT(= FALSE);
				// whether Visual mode is active
VIsual_select INIT(= FALSE);
				// whether Select mode is active
VIsual_select_reg INIT(= 0);
				// register name for Select mode
restart_VIsual_select INIT(= 0);
				// restart Select mode when next cmd finished
VIsual_reselect = 0;
				// whether to restart the selection after a
				// Select mode mapping or menu

VIsual_mode INIT(= 'v');
				// type of Visual mode

redo_VIsual_busy INIT(= FALSE);
				// TRUE when redoing Visual

/*
 * The Visual area is remembered for reselection.
 */
resel_VIsual_mode INIT(= NUL);	// 'v', 'V', or Ctrl-V
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
did_ai INIT(= FALSE);

/*
 * Column of first char after autoindent.  0 when no autoindent done.  Used
 * when 'backspace' is 0, to avoid backspacing over autoindent.
 */
ai_col INIT(= 0);

/*
 * This is a character which will end a start-middle-end comment when typed as
 * the first character on a new line.  It is taken from the last character of
 * the "end" comment leader when the COM_AUTO_END flag is given for that
 * comment end in 'comments'.  It is only valid when did_ai is TRUE.
 */
end_comment_pending INIT(= NUL);

/*
 * This flag is set after a ":syncbind" to let the check_scrollbind() function
 * know that it should not attempt to perform scrollbinding due to the scroll
 * that was a result of the ":syncbind." (Otherwise, check_scrollbind() will
 * undo some of the work done by ":syncbind.")  -ralston
 */
did_syncbind INIT(= FALSE);

/*
 * This flag is set when a smart indent has been performed. When the next typed
 * character is a '{' the inserted tab will be deleted again.
 */
did_si INIT(= FALSE);

/*
 * This flag is set after an auto indent. If the next typed character is a '}'
 * one indent will be removed.
 */
can_si INIT(= FALSE);

/*
 * This flag is set after an "O" command. If the next typed character is a '{'
 * one indent will be removed.
 */
can_si_back INIT(= FALSE);

old_indent INIT(= 0);	// for ^^D command in insert mode

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
orig_line_count INIT(= 0);  // Line count when "gR" started
vr_lines_changed INIT(= 0); // #Lines changed by "gR" so far

#if defined(FEAT_X11) && defined(FEAT_XCLIPBOARD)
/* argument to SETJMP() for handling X IO errors */
x_jump_env = NULL;
#endif

















enc_dbcs INIT(= 0);		// One of DBCS_xxx values if
						// DBCS encoding
enc_unicode INIT(= 0);	// 2: UCS-2 or UTF-16, 4: UCS-4
enc_utf8 INIT(= FALSE);		// UTF-8 encoded Unicode
enc_latin1like INIT(= TRUE);	// 'encoding' is latin1 comp.
#if defined(MSWIN) || defined(FEAT_CYGWIN_WIN32_CLIPBOARD)
// Codepage nr of 'encoding'.  Negative means it's not been set yet, zero
// means 'encoding' is not a valid codepage.
enc_codepage INIT(= -1);
enc_latin9 INIT(= FALSE);	// 'encoding' is latin9
#endif
has_mbyte INIT(= 0);		// any multi-byte encoding

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

// Convert char "c" to bytes in "buf", return the length.  "buf" must have room
// for at least 6 bytes.
mb_char2bytes = latin_char2bytes;

mb_ptr2cells = latin_ptr2cells;
mb_ptr2cells_len = latin_ptr2cells_len;
mb_char2cells = latin_char2cells;
mb_off2cells = latin_off2cells;
mb_ptr2char = latin_ptr2char;

// Byte offset from "p" to the start of a character, including any composing
// characters. "base" must be the start of the string, which must be NUL
// terminated.
mb_head_off = latin_head_off;


#ifdef FEAT_XIM
# ifdef FEAT_GUI_GTK
xic INIT(= NULL);
/*
 * Start and end column of the preedit area in virtual columns from the start
 * of the text line.  When there is no preedit area they are set to MAXCOL.
 * "preedit_end_col" is needed for coloring the preedited string.  Drawing the
 * color between "preedit_start_col" and curpos did not work, because some XIM
 * set the cursor position to the first char of the string.
 */
preedit_start_col INIT(= MAXCOL);
preedit_end_col INIT(= MAXCOL);

// "xim_changed_while_preediting" is set when changed() can set the 'modified'
// flag even while preediting.
	xim_changed_while_preediting INIT(= FALSE);
# else
xic INIT(= NULL);
# endif
# ifdef FEAT_GUI
xim_fg_color INIT(= INVALCOLOR);
xim_bg_color INIT(= INVALCOLOR);
# endif
#endif

/*
 * "State" is the main state of Vim.
 * There are other variables that modify the state:
 * "Visual_mode"    When State is MODE_NORMAL or MODE_INSERT.
 * "finish_op"	    When State is MODE_NORMAL, after typing the operator and
 *		    before typing the motion command.
 * "motion_force"   Last motion_force  from do_pending_operator()
 * "debug_mode"	    Debug mode.
 */
State INIT(= MODE_NORMAL);

#ifdef FEAT_EVAL
debug_mode INIT(= FALSE);
#endif

finish_op INIT(= FALSE);// TRUE while an operator is pending
opcount INIT(= 0);	// count for pending operator
motion_force INIT(= 0); // motion force for pending operator

/*
 * Ex mode (Q) state
 */
exmode_active INIT(= 0);	// zero, EXMODE_NORMAL or EXMODE_VIM

// Flag set when main_loop() should exit when entering Ex mode.
pending_exmode_active INIT(= FALSE);

ex_no_reprint INIT(= FALSE); // no need to print after z or p

reg_recording INIT(= 0);	// register for recording  or zero
reg_executing INIT(= 0);	// register being executed or zero
// Flag set when peeking a character and found the end of executed register
pending_end_reg_executing INIT(= 0);

// Set when a modifyOtherKeys sequence was seen, then simplified mappings will
// no longer be used.
seenModifyOtherKeys INIT(= FALSE);

no_mapping INIT(= FALSE);	// currently no mapping allowed
no_zero_mapping INIT(= 0);	// mapping zero not allowed
allow_keys INIT(= FALSE);	// allow key codes when no_mapping
					// is set
no_reduce_keys INIT(= FALSE);  // do not apply Ctrl, Shift and Alt
					  // to the key
no_u_sync INIT(= 0);		// Don't call u_sync()
#ifdef FEAT_EVAL
u_sync_once INIT(= 0);	// Call u_sync() once when evaluating
					// an expression.
#endif

restart_edit INIT(= 0);	// call edit when next cmd finished
arrow_used = 0;			// Normally FALSE, set to TRUE after
					// hitting cursor key in insert mode.
					// Used by vgetorpeek() to decide when
					// to call u_sync()
ins_at_eol INIT(= FALSE); // put cursor after eol when
					  // restarting edit after CTRL-O

no_abbr INIT(= TRUE);	// TRUE when no abbreviations loaded

#ifdef USE_EXE_NAME
exe_name = NULL;		// the name of the executable
#endif

#ifdef USE_ON_FLY_SCROLL
dont_scroll INIT(= FALSE);// don't use scrollbars when TRUE
#endif
mapped_ctrl_c INIT(= FALSE); // modes where CTRL-C is mapped
ctrl_c_interrupts INIT(= TRUE);	// CTRL-C sets got_int

// EXTERN cmdmod_T	cmdmod;			// Ex command modifiers
sticky_cmdmod_flags INIT(= 0); // used by :execute

#ifdef FEAT_EVAL
is_export INIT(= FALSE);    // :export {cmd}
#endif

msg_silent INIT(= 0);	// don't print messages
emsg_silent INIT(= 0);	// don't print error messages
#ifdef FEAT_EVAL
emsg_silent_def INIT(= 0);  // value of emsg_silent when a :def
					    // function is called
#endif
emsg_noredir INIT(= 0);	// don't redirect error messages
cmd_silent INIT(= FALSE); // don't echo the command line

in_assert_fails INIT(= FALSE);	// assert_fails() active

swap_exists_action INIT(= SEA_NONE);
					// For dialog when swap file already
					// exists.
swap_exists_did_quit INIT(= FALSE);
					// Selected "quit" at the dialog.

IObuff = NULL;		// sprintf's are done in this buffer,
					// size is IOSIZE
NameBuff = NULL;		// file names are expanded in this
					// buffer, size is MAXPATHL
// When non-zero, postpone redrawing.
RedrawingDisabled INIT(= 0);

readonlymode INIT(= FALSE); // Set to TRUE for "view"
recoverymode INIT(= FALSE); // Set to TRUE for "-r" option

typebuf	= (typebuf_T) {NULL, NULL, 0, 0, 0, 0, 0, 0, 0} ; // typeahead buffer




ex_normal_busy INIT(= 0);   // recursiveness of ex_normal()
#ifdef FEAT_EVAL
in_feedkeys INIT(= 0);	    // ex_normal_busy set in feedkeys()
#endif
ex_normal_lock INIT(= 0);   // forbid use of ex_normal()

#ifdef FEAT_EVAL
ignore_script INIT(= FALSE);  // ignore script input
#endif
stop_insert_mode = 0;	// for ":stopinsert" and 'insertmode'

KeyTyped = 0;		// TRUE if user typed current char
KeyStuffed = 0;		// TRUE if current char from stuffbuf
#ifdef HAVE_INPUT_METHOD
vgetc_im_active = 0;	// Input Method was active for last
					// character obtained from vgetc()
#endif
maptick INIT(= 0);	// tick for each non-mapped char

must_redraw INIT(= 0);	    // type of redraw necessary
skip_redraw INIT(= FALSE);  // skip redraw once
do_redraw INIT(= FALSE);    // extra redraw once
#ifdef FEAT_DIFF
need_diff_redraw INIT(= 0); // need to call diff_redraw()
#endif

need_highlight_changed INIT(= TRUE);

#define NSCRIPT 15
// EXTERN FILE	*scriptin[NSCRIPT];	    // streams to read script from
curscript INIT(= 0);	    // index in scriptin[]
scriptout  INIT(= NULL);   // stream to write script to
read_cmd_fd INIT(= 0);	    // fd to read commands from

// Set to TRUE when an interrupt signal occurred.
// Volatile because it is used in signal handler catch_sigint().
got_int INIT(= FALSE);

// Set to TRUE when SIGUSR1 signal was detected.
// Volatile because it is used in signal handler catch_sigint().
got_sigusr1 INIT(= FALSE);

#ifdef USE_TERM_CONSOLE
term_console INIT(= FALSE); // set to TRUE when console used
#endif
termcap_active INIT(= FALSE);	// set by starttermcap()
cur_tmode INIT(= TMODE_COOK);	// input terminal mode
bangredo INIT(= FALSE);	    // set to TRUE with ! command
searchcmdlen = 0;		    // length of previous search cmd
#ifdef FEAT_SYN_HL
reg_do_extmatch INIT(= 0);  // Used when compiling regexp:
					    // REX_SET to allow \z\(...\),
					    // REX_USE to allow \z\1 et al.
reg_extmatch_T *re_extmatch_in INIT(= NULL); // Used by vim_regexec():
					    // strings for \z\1...\z\9
reg_extmatch_T *re_extmatch_out INIT(= NULL); // Set by vim_regexec()
					    // to store \z\(...\) matches
#endif

did_outofmem_msg INIT(= FALSE);
					    // set after out of memory msg
did_swapwrite_msg INIT(= FALSE);
					    // set after swap write error msg
undo_off INIT(= FALSE);	    // undo switched off for now
global_busy INIT(= 0);	    // set when :global is executing
listcmd_busy INIT(= FALSE); // set when :argdo, :windo or
					    // :bufdo is executing
need_start_insertmode INIT(= FALSE);
					    // start insert mode soon
#if defined(FEAT_EVAL) || defined(PROTO)
// EXTERN char_u	last_mode[MODE_MAX_LENGTH] INIT(= "n"); // for ModeChanged event
#endif
last_cmdline INIT(= NULL); // last command line (for ":)
repeat_cmdline INIT(= NULL); // command line for "."
new_last_cmdline INIT(= NULL);	// new value for last_cmdline
autocmd_fname INIT(= NULL); // fname for <afile> on cmdline
autocmd_fname_full = 0;	     // autocmd_fname is full path
autocmd_bufnr INIT(= 0);     // fnum for <abuf> on cmdline
autocmd_match INIT(= NULL); // name for <amatch> on cmdline
did_cursorhold INIT(= FALSE); // set when CursorHold t'gerd
last_cursormoved = (pos_T) {0, 0, 0} ;	      // for CursorMoved event


postponed_split INIT(= 0);  // for CTRL-W CTRL-] command
postponed_split_flags INIT(= 0);  // args for win_split()
postponed_split_tab INIT(= 0);  // cmdmod.tab
#ifdef FEAT_QUICKFIX
g_do_tagpreview INIT(= 0);  // for tag preview commands:
					    // height of preview window
#endif
g_tag_at_cursor INIT(= FALSE); // whether the tag command comes
					    // from the command line (0) or was
					    // invoked as a normal command (1)

replace_offset INIT(= 0);   // offset for replace_push()

escape_chars INIT(= (char_u *)" \t\\\"|");
					    // need backslash in cmd line

keep_help_flag INIT(= FALSE); // doing :ta from help file

/*
 * When a string option is NULL (which only happens in out-of-memory
 * situations), it is set to empty_option, to avoid having to check for NULL
 * everywhere.
 */
empty_option INIT(= (char_u *)"");

redir_off INIT(= FALSE);	// no redirection for a moment
redir_fd INIT(= NULL);	// message redirection file
#ifdef FEAT_EVAL
redir_reg INIT(= 0);	// message redirection register
redir_vname INIT(= 0);	// message redirection variable
redir_execute INIT(= 0);	// execute() redirection
#endif

#ifdef FEAT_WILDMENU
save_p_ls INIT(= -1);	// Save 'laststatus' setting
save_p_wmh INIT(= -1);	// Save 'winminheight' setting
wild_menu_showing INIT(= 0);
#endif

homedir INIT(= NULL);

// When a window has a local directory, the absolute path of the global
// current directory is stored here (in allocated memory).  If the current
// directory is not a local directory, globaldir is NULL.
globaldir INIT(= NULL);

// Characters from 'fillchars' option
fill_stl INIT(= ' ');
fill_stlnc INIT(= ' ');
fill_vert INIT(= ' ');
fill_fold INIT(= '-');
fill_foldopen INIT(= '-');
fill_foldclosed INIT(= '+');
fill_foldsep INIT(= '|');
fill_diff INIT(= '-');
fill_eob INIT(= '~');

#ifdef FEAT_FOLDING
disable_fold_update INIT(= 0);
#endif

// Whether 'keymodel' contains "stopsel" and "startsel".
km_stopsel INIT(= FALSE);
km_startsel INIT(= FALSE);

#ifdef FEAT_CMDWIN
cmdwin_type INIT(= 0);	// type of cmdline window or 0
cmdwin_result INIT(= 0); // result of cmdline window or 0
#endif

// no_lines_msg	= N_("--No lines in buffer--");

/*
 * When ":global" is used to number of substitutions and changed lines is
 * accumulated until it's finished.
 * Also used for ":spellrepall".
 */
sub_nsubs = 0;	// total number of substitutions
sub_nlines = 0;	// total number of lines changed

#ifdef FEAT_EVAL
// Used when a compiled :substitute has an expression.
substitute_instr INIT(= NULL);
#endif

// table to store parsed 'wildmode'
// EXTERN char_u	wim_flags[4];

#if defined(FEAT_STL_OPT)
// whether titlestring and iconstring contains statusline syntax
// # define STL_IN_ICON	1
// # define STL_IN_TITLE	2
stl_syntax INIT(= 0);
#endif

#if defined(FEAT_BEVAL) && !defined(NO_X11_INCLUDES)
balloonEval INIT(= NULL);
balloonEvalForTerm INIT(= FALSE);
# if defined(FEAT_NETBEANS_INTG)
bevalServers INIT(= 0);
# endif
#endif

#if (defined(FEAT_PRINTER) && defined(FEAT_STL_OPT)) \
	    || defined(FEAT_GUI_TABLINE)
// Page number used for %N in 'pageheader' and 'guitablabel'.
printer_page_num = 0;
#endif

#ifdef FEAT_XCLIPBOARD
// xterm display name
xterm_display INIT(= NULL);

// whether xterm_display was allocated, when FALSE it points into argv[]
xterm_display_allocated INIT(= FALSE);

// xterm display pointer
xterm_dpy INIT(= NULL);
#endif
#if defined(FEAT_XCLIPBOARD) || defined(FEAT_GUI_X11)
app_context INIT(= (XtAppContext)NULL);
#endif

#ifdef FEAT_GUI_GTK
gtk_socket_id INIT(= 0);
echo_wid_arg INIT(= FALSE);	// --echo-wid argument
#endif

#ifdef FEAT_GUI_MSWIN
/*
 * The value of the --windowid argument.
 * For embedding gvim inside another application.
 */
win_socket_id INIT(= 0);
#endif

#if defined(FEAT_CLIENTSERVER) || defined(FEAT_EVAL)
typebuf_was_filled INIT(= FALSE); // received text from client
						  // or from feedkeys()
#endif

#ifdef FEAT_CLIENTSERVER
serverName INIT(= NULL);	// name of the server
# ifdef FEAT_X11
commWindow INIT(= None);
clientWindow INIT(= None);
commProperty INIT(= None);
serverDelayedStartName INIT(= NULL);
# else



clientWindow INIT(= 0);
# endif
#endif

#if defined(UNIX) || defined(VMS)
term_is_xterm INIT(= FALSE);	// xterm-like 'term'
#endif

#ifdef BACKSLASH_IN_FILENAME
psepc INIT(= '\\');	// normal path separator character
psepcN INIT(= '/');	// abnormal path separator character
// normal path separator string
pseps[2] INIT2('\\', 0);
#endif

// Set to TRUE when an operator is being executed with virtual editing, MAYBE
// when no operator is being executed, FALSE otherwise.
virtual_op INIT(= MAYBE);

#ifdef FEAT_SYN_HL
// Display tick, incremented for each call to update_screen()
display_tick INIT(= 0);
#endif

#ifdef FEAT_SPELL
// Line in which spell checking wasn't highlighted because it touched the
// cursor position in Insert mode.
spell_redraw_lnum INIT(= 0);
#endif

#ifdef FEAT_CONCEAL
// Set when the cursor line needs to be redrawn.
need_cursor_line_redraw INIT(= FALSE);
#endif

#ifdef USE_MCH_ERRMSG
// Grow array to collect error messages in until they can be displayed.
error_ga = (garray_T) {0, 0, 0, 0, NULL} ;
#endif

#ifdef FEAT_NETBEANS_INTG
netbeansArg INIT(= NULL);	// the -nb[:host:port:passwd] arg
netbeansFireChanges INIT(= 1); // send buffer changes if != 0
netbeansForcedQuit INIT(= 0);// don't write modified files
netbeansReadFile INIT(= 1);	// OK to read from disk if != 0
netbeansSuppressNoLines INIT(= 0); // skip "No lines in buffer"
#endif

/*
 * Some messages that can be shared are included here.
 */
strcpy(top_bot_msg, "search hit TOP, continuing at BOTTOM");
strcpy(bot_top_msg, "search hit BOTTOM, continuing at TOP");

#ifdef FEAT_EVAL
strcpy(line_msg, " line ");
#endif

#ifdef FEAT_CRYPT
strcpy(need_key_msg, "Need encryption key for \"%s\"");
#endif

/*
 * Comms. with the session manager (XSMP)
 */
#ifdef USE_XSMP
xsmp_icefd INIT(= -1);   // The actual connection
#endif

// For undo we need to know the lowest time possible.
starttime = 0;

#ifdef STARTUPTIME
time_fd INIT(= NULL);  // where to write startup timing
#endif

/*
 * Some compilers warn for not using a return value, but in some situations we
 * can't do anything useful with the value.  Assign to this variable to avoid
 * the warning.
 */
vim_ignored = 0;
vim_ignoredp = NULL;

#ifdef FEAT_EVAL
// set by alloc_fail(): ID
alloc_fail_id INIT(= aid_none);
// set by alloc_fail(), when zero alloc() returns NULL
alloc_fail_countdown INIT(= -1);
// set by alloc_fail(), number of times alloc() returns NULL
alloc_fail_repeat INIT(= 0);

// flags set by test_override()
disable_char_avail_for_testing INIT(= FALSE);
disable_redraw_for_testing INIT(= FALSE);
ignore_redraw_flag_for_testing INIT(= FALSE);
nfa_fail_for_testing INIT(= FALSE);
no_query_mouse_for_testing INIT(= FALSE);
ui_delay_for_testing INIT(= 0);
reset_term_props_on_termresponse INIT(= FALSE);
disable_vterm_title_for_testing INIT(= FALSE);
override_sysinfo_uptime INIT(= -1);
override_autoload INIT(= FALSE);

in_free_unref_items INIT(= FALSE);
#endif

#ifdef FEAT_TIMERS
did_add_timer INIT(= FALSE);
timer_busy INIT(= 0);   // when timer is inside vgetc() then > 0
#endif
#ifdef FEAT_EVAL
input_busy INIT(= 0);   // when inside get_user_input() then > 0

lval_root INIT(= NULL);
#endif

#ifdef FEAT_BEVAL_TERM
bevalexpr_due_set INIT(= FALSE);
bevalexpr_due = 0;
#endif

#ifdef FEAT_EVAL
time_T time_for_testing INIT(= 0);

// Abort conversion to string after a recursion error.
did_echo_string_emsg INIT(= FALSE);

// Used for checking if local variables or arguments used in a lambda.
eval_lavars_used INIT(= FALSE);
#endif

#ifdef MSWIN
ctrl_break_was_pressed INIT(= FALSE);
g_hinst INIT(= NULL);
#endif

#if defined(FEAT_JOB_CHANNEL)
did_repeated_msg INIT(= 0);
// # define REPEATED_MSG_LOOKING	    1
// # define REPEATED_MSG_SAFESTATE	    2

// This flag is set when outputting a terminal control code and reset in
// out_flush() when characters have been written.
ch_log_output INIT(= FALSE);

// Whether a redraw is needed for appending a line to a buffer.
channel_need_redraw INIT(= FALSE);

// #define FOR_ALL_CHANNELS(ch) \
//     for ((ch) = first_channel; (ch) != NULL; (ch) = (ch)->ch_next)
// #define FOR_ALL_JOBS(job) \
//     for ((job) = first_job; (job) != NULL; (job) = (job)->jv_next)
#endif
// 
// #if defined(FEAT_DIFF)
// #define FOR_ALL_DIFFBLOCKS_IN_TAB(tp, dp) \
//     for ((dp) = (tp)->tp_first_diff; (dp) != NULL; (dp) = (dp)->df_next)
// #endif
// 
// #define FOR_ALL_LIST_ITEMS(l, li) \
//     for ((li) = (l) == NULL ? NULL : (l)->lv_first; (li) != NULL; (li) = (li)->li_next)

// While executing a regexp and set to OPTION_MAGIC_ON or OPTION_MAGIC_OFF this
// overrules p_magic.  Otherwise set to OPTION_MAGIC_NOT_SET.
magic_overruled INIT(= OPTION_MAGIC_NOT_SET);
