/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const int gappx 		    = 15;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int focusonwheel       = 0;

static const char *fonts[]          = { "hack:size=20", "Symbols Nerd Font:style=2048-em:pixelsize=30" };
static const char dmenufont[]       = "hack:size=20" ;
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_orange[]	    = "#ffb947";
static const char col_green[]	    = "#3cc23a";
static const char col_purple[]	    = "#6042f5";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeInv]  = { col_gray1, col_gray3, col_gray2 },
	[SchemeSel]  = { col_gray4, col_purple,  col_cyan },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	instance            title       			tags mask     	isfloating   isfreesize		moniitor    float x,y,w,h         floatborderpx */
	{ "Zoom",     	NULL,               "Polls",    			0,		1,           1,			-1 ,        50,50,500,500,        5 },           
	{ "Zoom",     	NULL,               "Chat",     			0,		1,           1,       		-1 ,        50,50,500,500,        5 },           
	/* { "Gimp",     	NULL,       	NULL,       			0,		1,           1,			-1 }, */
	{ "firefox",  	NULL,               NULL,       			0,		0,           0,			-1 ,        50,50,500,500,        5 },           
	{ "st",       	NULL,               NULL,       			0,		0,           0,			-1 ,        50,50,500,500,        5 },           
	{ "St",       	NULL,               NULL,       			0,		0,           0,			-1 ,        50,50,500,500,        5 },  /* St with Xresources patch */
	{ "Alacritty",  NULL,               NULL,       			0,		0,           0,			-1 ,        50,50,500,500,        5 },  /* St with Xresources patch */
	{ "Zathura",    "org.pwmt.zathura", NULL,       			0,		0,           0,			-1 ,        50,50,500,500,        5 },  /* St with Xresources patch */
	{ "Nemo",     NULL,       	    NULL,       			0,		1,           0,			-1 ,        850,450,1300,800,        5 },           
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     	arrange function */
	{ "[T]=",      	tile },    /* first entry is default */
	{ "[F]=",      	NULL },    /* no layout function means floating behavior */
	{ "[M]=",      	monocle },
	{ "[D]=",       deck },
	{ "[TTT]",      bstack },
	{ "[===]",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* resetnmaster patch */
void resetnmaster(const Arg *arg);

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char dmenuhp[] = "firefox,chromium,icecat";
static const char *dmenucmd[] = { "dmenu_run_history", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-hp", dmenuhp , NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *alttermcmd[]  = { "st", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";
static const char *browser[]  = { "firefox", NULL };
static const char *browserlist[]  = { "browsers", NULL };
static const char *files[]  = { "nemo", NULL };
static const char *altfiles[]  = { "st", "-e", "lf", NULL };
static const char *dmenuunicode[]  = { "dmenuunicode", NULL };
static const char *clipmenu[]  = { "clipmenu", NULL };
static const char *bitwarden[]  = { "bwm", NULL };
static const char *email[]  = { "alacritty", "-e", "neomutt", NULL };
static const char *news[]  = { "alacritty", "-e", "newsboat", NULL };
static const char *overflow[]  = { "/home/brandon/.repos/dwmblocks/overflow/Swap.sh", NULL };


static Key keys[] = {
	/* modifier                     key        		        function        argument */
	{ MODKEY,                       XK_d,      		        spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, 		        spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, 		        spawn,          {.v = alttermcmd } },
	{ MODKEY,            	        XK_f, 		                spawn,          {.v = files } },
	{ MODKEY|ShiftMask,            	XK_f, 		                spawn,          {.v = altfiles } },
	{ MODKEY,             		XK_w,	 		        spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,             XK_w,	 		        spawn,          {.v = browserlist } },
	{ MODKEY,             		XK_grave,	 	        spawn,          {.v = dmenuunicode } },
	{ MODKEY,             		XK_x, 			        spawn,          {.v = clipmenu } },
	{ MODKEY,             		XK_p, 			        spawn,          {.v = bitwarden } },
	{ MODKEY,             		XK_e, 			        spawn,          {.v = email } },
	{ MODKEY,             		XK_n, 			        spawn,          {.v = news } },
	{ MODKEY,                       XK_b,      		        togglebar,      {0} },
	{ MODKEY,                       XK_j,      		        focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      		        focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_j,			        pushdown,       {0} },
	{ MODKEY|ShiftMask,		XK_k,			        pushup,         {0} },
	{ MODKEY,                       XK_bracketleft,      	        incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_bracketright,      	        incnmaster,     {.i = -1 } },
	{ MODKEY,           		XK_backslash,		        resetnmaster,   {0} },
	{ MODKEY,                       XK_h,      		        setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      		        setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      		        setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      		        setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      		        setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_z, 			        zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_h,      		        setsmfact,      {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_l,      		        setsmfact,      {.f = -0.05} },
/*	{ MODKEY,                       XK_Tab,    		        view,           {0} }, */
	{ MODKEY,             		XK_q,     		        killclient,     {0} },
	{ MODKEY,                       XK_t,      		        setlayout,      {.v = &layouts[0]} },
	/* { MODKEY,                       XK_f,      		        setlayout,      {.v = &layouts[1]} }, */
	{ MODKEY,                       XK_m,      		        setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      		        setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,                           setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_o,      		        setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_space,  		        spawn,          {.v = overflow } },
	{ MODKEY|ShiftMask,             XK_space,  		        togglefloating, {0} },
	{ MODKEY,                       XK_0,      		        view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      		        tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  		        focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 		        focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  		        tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, 		        tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus, 		        setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  		        setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  		        setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Print,                       quit,            {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
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
};

/* more for resetnmaster */
void
resetnmaster(const Arg *arg)
{
		selmon->nmaster = 1;
		arrange(selmon);
}
