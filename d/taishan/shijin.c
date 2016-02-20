//Cracked by Roath
// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

inherit ROOM;

int do_study(string);

void create()
{
	set("short", "��ʯ��");
	set("long", @LONG
������һ���ʯƺ��ʯ�����׭�ġ���վ�������������綷����ȴû�м�
�ؿ�ʯ�ߵ����ֺͿ�ʯ����������˴˴��������ɽ��ɽ·Խ��Խ�������ˡ�
LONG
	);

	set("exits", ([
		"northup" : __DIR__"huima",
		"westdown" : __DIR__"doumo",
	]));

	set("objects",([
		__DIR__"npc/seng-ren" : 1,
	]));
	set("no_clean_up", 1);
	set("outdoors", "taishan");
	set("cost", 4);
	setup();
}

void init()
{
	add_action("do_study", "study");
	add_action("do_study", "du");
}


int do_study(string arg)
{
	object me;

	me = this_player();

	if ( !arg || ( arg != "stone" ) )
		return notify_fail("ʲô��\n");

	if ( (int)me->query_skill("literate", 1) < 1)
		return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

	if (me->query("jing") < 45)
		return notify_fail("��ľ����ܼ��С�\n");

	me->receive_damage("jing", 30);

	message_vision("$N��ר���ж�ʯƺ�ϵġ���վ�����\n", me);

	if ( (int)me->query_skill("buddhism", 1) < 100)
	{
		me->improve_skill("buddhism", me->query("int"));
		write("�����ʯƺ�ϵġ���վ�����ĥ��һ�ض����ƺ��������ķ������ĵá�\n");
		return 1;
	}

	write("�����ʯƺ����һ�ض�������������˵�ķ���̫��ǳ�ԣ�������˵�Ѻ��������ˡ�\n");

	return 1;
}

