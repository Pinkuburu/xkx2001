//Cracked by Roath
// Room: /d/beijing/east/guozihoutang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ��ʲ��Ҳû�еĿշ��䡣
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"guozihouyuan",
  "south" : __DIR__"guozidating",
]));
	set("no_clean_up", 0);

	setup();
	replace_program(ROOM);
}