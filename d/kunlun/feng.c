//Cracked by Roath
// Room: /d/mingjiao/feng.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���˹�����ʹ���·����š������������һ����ɱ����֮����������
�ϵ������λεľ������а���һ�Ż�Ƥ���Ρ������Ž��ڳ�����������
����Ϣ�����ص�ͷ�߹���
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"guangchang74",
]));
	set("no_clean_up", 0);
	set("cost", 1);

	setup();
	replace_program(ROOM);
}