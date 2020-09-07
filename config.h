/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 0;        /* border pixel of windows */
static const unsigned int snap           = 20;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;     /* 0 means no systray */
static const unsigned int gappih         = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv         = 20;       /* vert inner gap between windows */
static const unsigned int gappoh         = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 20;       /* vert outer gap between windows and screen edge */
static const int smartgaps               = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means bottom bar */
static const int focusonwheel            = 0;
static const char *fonts[]               = { "VictorMonoNerdFont:size=16", "JoyPixels:pixelsize=18:antialias=true:autohint=true"  };
static char dmenufont[]                  = "VictorMonoNerdFont:size=16";
static char normbgcolor[]                = "#E6E3F7";
static char normbordercolor[]            = "#E6E3F7";
static char normfgcolor[]                = "#25188B";
static char selfgcolor[]                 = "#FF4081";
static char selbordercolor[]             = "#C9C4EE";
static char selbgcolor[]                 = "#C9C4EE";
static char statusfgcolor[]                = "#ffffff";
static char statusbgcolor[]                = "#FF5792";
static char statusbdcolor[]                = "#FF5792";

// patch systray to use SchemeStatus , check bg color is bit darker when applied
static char *colors[][3]                 = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	   [SchemeStatus]  = { statusfgcolor, statusbgcolor,  statusbdcolor  }, // Statusbar right {text,background,not used but cannot be empty}
	   [SchemeTagsSel]  = { selfgcolor, selbgcolor,  selbordercolor  }, // Tagbar left selected {text,background,not used but cannot be empty}
       [SchemeTagsNorm]  = { normfgcolor, normbgcolor,  normbordercolor  }, // Tagbar left unselected {text,background,not used but cannot be empty}
       [SchemeInfoSel]  = { selfgcolor, selbgcolor,  selbordercolor  }, // infobar middle  selected {text,background,not used but cannot be empty}
       [SchemeInfoNorm]  = { normfgcolor, normbgcolor,  normbordercolor  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
    "dwmblocks", NULL,
    "dunst", NULL,
    "fusuma", NULL,
    "sh", "-c", "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
    "clipmenud", NULL,
    "optimus-manager-qt", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { " ¹", " ²", "﬏ ³", " ⁴", " ⁵", " ⁶", " ⁷", " ⁸", "💻⁹" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance                title       tags mask     isfloating   isterminal noswallow monitor */
	{ "firefox",            NULL,                   NULL,       1 << 1,       0,           0,         1,        -1 },
	{ "Brave-browser",      NULL,                   NULL,       1 << 1,       0,           0,         1,        -1 },
	{ "code-oss",           NULL,                   NULL,       1 << 2,       0,           0,         1,        -1 },
	{ "DesktopEditors",     NULL,                   NULL,       1 << 2,       0,           0,         1,        -1 },
	{ "Google-chrome",      "google-chrome",        NULL,       1 << 3,       0,           0,         1,        -1 },
	{ NULL,NULL,            "Android Emulator - dev:5554",      1 << 4,       1,           0,         1,        -1 },
	{ "Gimp",               NULL,                   NULL,       1 << 5,       0,           0,         1,        -1 },
	{ "Inkscape",           NULL,                   NULL,       1 << 5,       0,           0,         1,        -1 },
	{ "kdenlive",           NULL,                   NULL,       1 << 5,       0,           0,         1,        -1 },
	{ "mpv",                NULL,                   NULL,       1 << 5,       0,           0,         1,        -1 },
	{ "Steam",              NULL,                   NULL,       1 << 6,       1,           0,         1,        -1 },
	{ "dota2",              NULL,                   NULL,       1 << 6,       0,           0,         1,        -1 },
	{ "Meld",               NULL,                   NULL,       1 << 7,       0,           0,         1,        -1 },
	{ "Postman",            NULL,                   NULL,       1 << 7,       0,           0,         1,        -1 },
	{ "Nemo",               NULL,                   NULL,       1 << 8,       0,           0,         1,        -1 },
	{ "Alacritty",          NULL,                   NULL,       0,            0,           1,         0,        -1 },
	{ "St",                 NULL,                   NULL,       0,            0,           1,         0,        -1 },
    { "Sirula",             NULL,                   NULL,       0,            1,           0,         1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.6;     /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;       /* number of clients in master area */
static const int resizehints = 1;       /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1                  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol                           arrange function */
 	{ "﬿",	tile },			            /* layout:0, Default: Master on left, slaves on right */
	{ "ﳶ",	bstack },		            /* layout:1, Master on top, slaves on bottom */

	{ "🍥",	spiral },		            /* layout:2, Fibonacci spiral */
	{ "侀",	dwindle },		            /* layout:3, Decreasing in size right and leftward */

	{ "",	deck },			            /* layout:4, Master on left, slaves in monocle-like mode on right */
 	{ "🂠",	monocle },		            /* layout:5, All windows on top of eachother */

	{ "恵",	centeredmaster },		    /* layout:6, Master in middle, slaves on sides */
	{ "",	centeredfloatingmaster },	/* layout:7, Same but master floats */

	{ "",	NULL },			            /* layout:8, no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "167x48", NULL };
static const char *clipboard[] = { "clipmenu", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor,"-i", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,			XK_Escape,	spawn,	   SHCMD("dmenuunicode") },
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_minus,	spawn,		SHCMD("rofi-ssh") },
	{ MODKEY|ShiftMask,	XK_minus,	spawn,		SHCMD("rofi -show ssh") },
	{ MODKEY,			XK_equal,	spawn,		SHCMD("addjournal") },
	{ MODKEY|ShiftMask,	XK_equal,	spawn,		SHCMD("st -e showjrnl") },
	{ MODKEY,			XK_BackSpace,	        spawn,	SHCMD("sysact") },
	{ MODKEY|ShiftMask,	XK_BackSpace,	        spawn,	SHCMD("killall redshift-gtk || redshift-gtk") },

	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY|ShiftMask,	XK_q,		spawn,	    SHCMD("{ killall compton || setsid compton & } ; xwallpaper --zoom ~/.config/wall.png") },
	{ MODKEY,	        XK_w,		spawn,		SHCMD("st -e nmtui") },
	{ MODKEY|ShiftMask,	XK_w,		spawn,		SHCMD("toggle_bluetooth") },
	{ MODKEY,	        XK_e,		spawn,		SHCMD("dmenu_edit") },
	/* this is for git bare repo commit */
	{ MODKEY|ShiftMask,	XK_e,		spawn,		SHCMD("dac") },
	{ MODKEY|ShiftMask,	XK_r,		spawn,		SHCMD("dmenu_fm") },
	{ MODKEY,			XK_r,		spawn,		SHCMD("st -e ranger") },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY|ShiftMask,	XK_t,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,	XK_y,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} },
	{ MODKEY|ShiftMask,	XK_u,		setlayout,	{.v = &layouts[5]} },
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} },
	{ MODKEY|ShiftMask,	XK_i,		setlayout,	{.v = &layouts[7]} },
	{ MODKEY,			XK_o,		incnmaster, {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_o,		incnmaster, {.i = -1 } },
	{ MODKEY,			XK_p,		spawn,		SHCMD("displayselect") },
	{ MODKEY|ShiftMask,	XK_p,		spawn,		SHCMD("recent") },
  //{ MODKEY,			XK_bracketleft,		spawn,		SHCMD("") },
  //{ MODKEY|ShiftMask,	XK_bracketleft,		spawn,		SHCMD("") },
  //{ MODKEY,			XK_bracketright,	spawn,		SHCMD("") },
  //{ MODKEY|ShiftMask,	XK_bracketright,	spawn,		SHCMD("") },
    { MODKEY,			XK_backslash,		    spawn,		SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY|ShiftMask,	XK_backslash,		    spawn,		SHCMD("mailsync") },
	{ MODKEY,		    XK_slash,	spawn,		SHCMD("mpc toggle") },
    { MODKEY|ShiftMask,	XK_slash,	spawn,		SHCMD("mpc stop") },
    { MODKEY,			XK_comma,	spawn,		SHCMD("mpc prev") },
	{ MODKEY,			XK_period,	spawn,		SHCMD("mpc next") },
    { MODKEY|ShiftMask,	XK_comma,	spawn,		SHCMD("lmc back 10") },
	{ MODKEY|ShiftMask,	XK_period,	spawn,		SHCMD("lmc forward 10") },
    { MODKEY,	        XK_a,		spawn,		SHCMD("st -e pulsemixer;pkill -RTMIN+10 dwmblocks") },
	{ MODKEY|ShiftMask,	XK_a,		spawn,		SHCMD("st -e alsamixer") },
    { MODKEY,		    XK_s,		spawn,		SHCMD("pavucontrol") },
	{ MODKEY|ShiftMask,	XK_s,		spawn,		SHCMD("newscaster") },
	{ MODKEY,			XK_d,		spawn,      {.v = dmenucmd } },
	{ MODKEY|ShiftMask,	XK_d,		togglegaps,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY|ShiftMask,	XK_f,		setlayout,	{.v = &layouts[8]} },
	{ MODKEY,			XK_g,		spawn,	    SHCMD("google-chrome-stable") },
	{ MODKEY|ShiftMask,	XK_g,		spawn,		SHCMD("firefox") },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.01} },
    { MODKEY|ShiftMask,	XK_h,		spawn,	    SHCMD("st -e ytop")},
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.01} },
    { MODKEY|ShiftMask,	XK_l,		spawn,		SHCMD("cabl") },
	{ MODKEY,			XK_apostrophe,	shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,	XK_apostrophe,	shiftview,	{ .i = 1 } },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
    { MODKEY|ShiftMask,	XK_Return,	spawn,		SHCMD("nemo") },
	{ MODKEY,		    XK_grave,	togglescratch,	{.v = scratchpadcmd } },

	{ MODKEY,			XK_z,		incrgaps,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_z,		incrgaps,	{.i = -1 } },
	{ MODKEY,			XK_x,		spawn,		SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
	{ MODKEY|ShiftMask,	XK_x,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && sudo -A shutdown -h now") },
	{ MODKEY,			XK_c,		spawn,		SHCMD("st -e calcurse") },
	{ MODKEY|ShiftMask,	XK_c,		spawn,		SHCMD("toggle_webcam") },
	{ MODKEY,			XK_v,		spawn,		{.v = clipboard } },
	{ MODKEY|ShiftMask,	XK_v,		spawn,		SHCMD("st -e $EDITOR -c \"VimwikiIndex\"") },
	{ MODKEY|ShiftMask,	XK_b,		togglebar,	{0} },
	{ MODKEY,	        XK_b,		spawn,		SHCMD("brave") },
	{ MODKEY,			XK_n,		spawn,		SHCMD("st -e newsboat") },
	{ MODKEY|ShiftMask,	XK_n,		spawn,		SHCMD("newsup") },
	{ MODKEY,			XK_m,		spawn,		SHCMD("st -e ncmpcpp") },
    { MODKEY|ShiftMask,	XK_m,		spawn,		SHCMD("mpc up") },

	{ MODKEY,			XK_Left,	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_Left,	tagmon,		{.i = -1 } },
	{ MODKEY,			XK_Right,	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_Right,	tagmon,		{.i = +1 } },

	{ MODKEY,			XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
	/* Alt and ctrl key bindings */
	{ MODKEY|ControlMask,	XK_l,		spawn,	    SHCMD("st -e tuts")},
    {ALTKEY,            XK_Insert,  spawn,      SHCMD("pickcolor")},

    { MODKEY,			XK_F1,		spawn,		SHCMD("ducksearch") },
	{ MODKEY,			XK_F2,		quit,		{1} },
	{ MODKEY,			XK_F3,		spawn,		SHCMD("toggle_screenkey") },
	{ MODKEY,			XK_F4,		spawn,		SHCMD("pavucontrol") },
	{ MODKEY,			XK_F5,		xrdb,		{.v = NULL } },
	{ MODKEY,			XK_F6,		spawn,		SHCMD("newsup") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("mailsync") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("toggle_touchpad") },
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },
	/* { MODKEY,			XK_F11,		spawn,		SHCMD("") }, */
	/* { MODKEY,			XK_F12,		spawn,		SHCMD("") }, */
	{ MODKEY,			XK_space,	            zoom,		{0} },
    { MODKEY|ShiftMask,	XK_space,	            spawn,		SHCMD("rofi-pass") },
	{ MODKEY,		    XK_semicolon,	        togglefloating,	{0} },
	{ MODKEY|ShiftMask,	XK_semicolon,		    togglesticky,	{0} },

	{ 0,				XK_Print,	spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,		XK_Print,	spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_Print,	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,	XK_Print,	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("xsel -c && xsel -bc") },

	{ 0, XF86XK_AudioMute,		    spawn,		SHCMD("lmc mute ;pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioMicMute,		spawn,		SHCMD("amixer set Capture toggle") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,	    SHCMD("lmc up 5 ;pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,	    SHCMD("lmc down 5 ;pkill -RTMIN+10 dwmblocks") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,	    SHCMD("sudo brightnessctl s +5%") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,	    SHCMD("sudo brightnessctl s 5%-") },
    { 0, XF86XK_Tools,	            spawn,		SHCMD("toggle_keyboard") },

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
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = -1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = 1} },
};
