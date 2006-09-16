#define SIZEOF_REV	41	/* Holds a SHA-1 and an ending NUL */
	char id[SIZEOF_REV];	/* Commit SHA1 ID */
string_ncopy_do(char *dst, size_t dstlen, const char *src, size_t srclen)
	if (srclen > dstlen - 1)
		srclen = dstlen - 1;
	strncpy(dst, src, srclen);
	dst[srclen] = 0;
/* Shorthands for safely copying into a fixed buffer. */

	string_ncopy_do(dst, sizeof(dst), src, sizeof(dst))

#define string_ncopy(dst, src, srclen) \
	string_ncopy_do(dst, sizeof(dst), src, srclen)
LINE(ACKED,	   "    Acked-by",	COLOR_YELLOW,	COLOR_DEFAULT,	0), \

	/* State flags */
	unsigned int selected:1;

	{ 'f',		REQ_VIEW_BLOB },
	regex_t *regex;		/* Pre-compiled regex */
	bool (*draw)(struct view *view, struct line *line, unsigned int lineno, bool selected);
	/* Select line */
	void (*select)(struct view *view, struct line *line);
	struct line *line;
	bool selected = (view->offset + lineno == view->lineno);
	bool draw_ok;

	line = &view->line[view->offset + lineno];

	if (selected) {
		line->selected = TRUE;
		view->ops->select(view, line);
	} else if (line->selected) {
		line->selected = FALSE;
		wmove(view->win, lineno, 0);
		wclrtoeol(view->win);
	}

	scrollok(view->win, FALSE);
	draw_ok = view->ops->draw(view, line, lineno, selected);
	scrollok(view->win, TRUE);

	return draw_ok;
	char buf[SIZEOF_STR];
	size_t bufpos = 0;
	assert(view_is_displayed(view));
	string_format_from(buf, &bufpos, "[%s]", view->name);
		string_format_from(buf, &bufpos, " %s", view->ref);
		string_format_from(buf, &bufpos, " - %s %d of %d (%d%%)",
				   view->ops->type,
				   view->lineno + 1,
				   view->lines,
				   lines);
			string_format_from(buf, &bufpos, " %lds", secs);
	if (view == display[current_view])
		wbkgdset(view->title, get_line_attr(LINE_TITLE_FOCUS));
	else
		wbkgdset(view->title, get_line_attr(LINE_TITLE_BLUR));

	werase(view->title);
	mvwaddnstr(view->title, 0, 0, buf, bufpos);
update_display_cursor(struct view *view)
do_scroll_view(struct view *view, int lines)
	bool redraw_current_line = FALSE;
	/* Move current line into the view. */
	if (view->lineno < view->offset) {
		view->lineno = view->offset;
		redraw_current_line = TRUE;
	} else if (view->lineno >= view->offset + view->height) {
		view->lineno = view->offset + view->height - 1;
		redraw_current_line = TRUE;
	}

	assert(view->offset <= view->lineno && view->lineno < view->lines);

		if (redraw_current_line)
			draw_view_line(view, view->lineno - view->offset);
	assert(view_is_displayed(view));

	do_scroll_view(view, lines);
move_view(struct view *view, enum request request)
	int scroll_steps = 0;
		scroll_steps = steps;
			scroll_steps = -view->offset;
				scroll_steps = view->lines - view->offset - 1;
				if (scroll_steps >= view->height)
					scroll_steps -= view->height - 1;
	}
	if (!view_is_displayed(view)) {
		view->offset += steps;
		view->ops->select(view, &view->line[view->lineno]);
	/* Repaint the old "current" line if we be scrolling */
	if (ABS(steps) < view->height)
		draw_view_line(view, view->lineno - steps - view->offset);
	if (scroll_steps) {
		do_scroll_view(view, scroll_steps);
	}

	/* Draw the current line */
	draw_view_line(view, view->lineno - view->offset);
static void search_view(struct view *view, enum request request);
			search_view(view, request);
search_view(struct view *view, enum request request)
	if (view->regex) {
		regfree(view->regex);
	} else {
		view->regex = calloc(1, sizeof(*view->regex));
		if (!view->regex)
			return;
	regex_err = regcomp(view->regex, opt_search, REG_EXTENDED);
		regerror(regex_err, view->regex, buf, sizeof(buf));
	string_copy(view->grep, opt_search);
		if (!string_format(view->cmd, format, id, opt_path))
		do_scroll_view(prev, lines);
		move_view(view, request);
			move_view(view, request);
			if (view_is_displayed(view))
			move_view(view, request);
		search_view(view, request);
pager_draw(struct view *view, struct line *line, unsigned int lineno, bool selected)
	if (selected) {
		/* Add <tag>-g<commit_id> "fake" reference. */
	if (bufpos == 0)
		return;

	if (regexec(view->regex, text, 1, &pmatch, 0) == REG_NOMATCH)
static void
pager_select(struct view *view, struct line *line)
{
	if (line->type == LINE_COMMIT) {
		char *text = line->data;

		string_copy(view->ref, text + STRING_SIZE("commit "));
		string_copy(ref_commit, view->ref);
	}
}

	pager_select,
/* Parse output from git-ls-tree(1):
	bool first_read = view->lines == 0;
	if (first_read) {
		if (string_format(buf, "Directory path /%s", opt_path) &&
		    string_format(buf, TREE_UP_FORMAT, view->ref) &&
	/* Move the current line to the first tree entry. */
	if (first_read)
		view->lineno++;

	enum open_flags flags = display[0] == view ? OPEN_SPLIT : OPEN_DEFAULT;
			size_t origlen = pathlen;
			char *data = line->data;
			if (!string_format_from(opt_path, &pathlen, "%s/", basename)) {
				opt_path[origlen] = 0;
				return TRUE;
			}
	return TRUE;
}

static void
tree_select(struct view *view, struct line *line)
{
	char *text = line->data;

	text += STRING_SIZE("100644 blob ");
	if (line->type == LINE_TREE_FILE) {
		string_ncopy(ref_blob, text, 40);
		/* Also update the blob view's ref, since all there must always
		 * be in sync. */

	} else if (line->type != LINE_TREE_DIR) {
		return;
	string_ncopy(view->ref, text, 40);
	tree_select,
	pager_select,
	char id[SIZEOF_REV];		/* SHA1 ID. */
main_draw(struct view *view, struct line *line, unsigned int lineno, bool selected)
	if (selected) {
		if (regexec(view->regex, text, 1, &pmatch, 0) != REG_NOMATCH)
static void
main_select(struct view *view, struct line *line)
{
	struct commit *commit = line->data;

	string_copy(view->ref, commit->id);
	string_copy(ref_commit, view->ref);
}

	main_select,
	update_display_cursor(view);
		if (opt_iconv == ICONV_NONE)