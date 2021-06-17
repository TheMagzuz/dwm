/* See LICENSE file for copyright and license details. */
#define FONTSIZE "14"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx 		= 4; 			/* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "CaskaydiaCove Nerd Font Mono:pixelsize=" FONTSIZE ":antialias=true:autohint=true", "Symbola:pixelsize=" FONTSIZE ":antialias=true:autohint=true" };
static const char dmenufont[]       = "monospace:size=" FONTSIZE;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col1[]            = "#ffffff";
static const char col2[]            = "#ffffff";
static const char col3[]            = "#ffffff";
static const char col4[]            = "#ffffff";
static const char col5[]            = "#ffffff";
static const char col6[]            = "#ffffff";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { col_gray3, col_gray1, col_gray2 },
	[SchemeCol1]  = { col1,      col_gray1, col_gray2 },
	[SchemeCol2]  = { col2,      col_gray1, col_gray2 },
	[SchemeCol3]  = { col3,      col_gray1, col_gray2 },
	[SchemeCol4]  = { col4,      col_gray1, col_gray2 },
	[SchemeCol5]  = { col5,      col_gray1, col_gray2 },
	[SchemeCol6]  = { col6,      col_gray1, col_gray2 },
	[SchemeSel]   = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "","爵", "", "5", "6", "7", "ﭮ", "" };

//static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	//[> class      instance    title       tags mask     isfloating   monitor <]
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
//};

static const Rule rules[] = {
	{ "discord", 		NULL, 		 	NULL, 			1 << 7, 			0, 						-1 },
	{ "spt", 				NULL, 			NULL, 			1 << 8, 			0, 						-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st" , NULL };
static const char scratchpadname[] = "calculator";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "50x20", "-e", "bc",  NULL };

#define LARGE_VOLUME_INCREMENT "5"
#define SMALL_VOLUME_INCREMENT "1"
static const char   *volumeuplargecmd[] = { "change-main-volume", "+" LARGE_VOLUME_INCREMENT, NULL };
static const char *volumedownlargecmd[] = { "change-main-volume", "-" LARGE_VOLUME_INCREMENT, NULL };
static const char   *volumeupsmallcmd[] = { "change-main-volume", "+" SMALL_VOLUME_INCREMENT, NULL };
static const char *volumedownsmallcmd[] = { "change-main-volume", "-" SMALL_VOLUME_INCREMENT, NULL };

static const char *mutecommand[] = { "mute-main", NULL };
static const char *playpausecommand[] = { "spotify-play-pause", NULL };

static const char *cyclekeyboardcommand[] = { "cycle-kb", NULL };

static const char *selecticoncommand[] = { "select-char-to-clipboard", NULL };

static const char *spotifynextcommand[] = { "spotify-skip-rewind", NULL };
static const char *spotifyprevcommand[] = { "spotify-skip-rewind", "1", NULL };

static const char *spotifycommand[] = { "st", "-c", "spt", "-e", "spt", NULL };

static const char *screenshotcommand[] = { "screenshot", NULL };

static const char *firefoxcommand[] = { "firefox", NULL };
static const char *firefoxprivatecommand[] = {"firefox", "--private-window", NULL};

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             					XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY, 											XK_equal,  spawn, 				 {.v = volumeuplargecmd } },
	{ MODKEY, 											XK_minus,  spawn, 				 {.v = volumedownlargecmd } },
	{ MODKEY|ShiftMask, 						XK_equal,  spawn, 				 {.v = volumeupsmallcmd } },
	{ MODKEY|ShiftMask, 						XK_minus,  spawn, 				 {.v = volumedownsmallcmd } },
	{ MODKEY,												XK_o, 		 spawn, 				 {.v =  mutecommand } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY, 											XK_bracketright, 	shiftview,   {.i = +1}},
	{ MODKEY, 											XK_bracketleft, 	shiftview,   {.i = -1}},
	{ MODKEY|ShiftMask, 						XK_bracketright, 	shifttag,   {.i = +1}},
	{ MODKEY|ShiftMask, 						XK_bracketleft, 	shifttag,   {.i = -1}},
	{ MODKEY, 											XK_c, 							spawn, 		{ .v = cyclekeyboardcommand}},
	{ MODKEY, 											XK_e, 							spawn, 		{ .v = selecticoncommand }}, 
	{ MODKEY, 											XK_F1, 							spawn, 		{ .v = spotifyprevcommand }},
	{ MODKEY, 											XK_F2, 							spawn, 		{ .v = spotifynextcommand }},
	{ MODKEY|ShiftMask, 						XK_s, 							spawn, 		{ .v = screenshotcommand }}, 
	{ MODKEY, 											XK_s, 							spawn, 		{ .v = spotifycommand }}, 
	{ MODKEY,                       XK_b,      					spawn,    { .v = firefoxcommand }},
	{ MODKEY|ShiftMask, 						XK_b, 							spawn, 		{ .v = firefoxprivatecommand }}, 
	{ 0, 											XF86XK_AudioRaiseVolume,  spawn, 				 {.v = volumeupsmallcmd } },
	{ 0, 											XF86XK_AudioLowerVolume,  spawn, 				 {.v = volumedownsmallcmd } },
	{ 0, 											XF86XK_AudioPlay,  spawn, 				 {.v = playpausecommand } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

