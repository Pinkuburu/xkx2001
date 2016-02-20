//Cracked by Roath
// npc: /d/xingxiu/npc/ke.c
// Jay 3/27/96
// modified by sdong for job system, 11/23/98

inherit NPC;
inherit F_MASTER;
int auto_perform();
string ask_job();
void reward_dest(object obj,object ob);
void destroy_dest(object obj,object ob);
void destroy_staff(object obj,object ob);
void thank_dest(object obj,object ob);

void create()
{
	set_name("ŷ����", ({ "ouyang ke", "ouyang", "ke" }));
	set("long", "��һ�����£����û�������̬����������˫Ŀб�ɣ���Ŀ���ţ�ȴ��Ӣ�����ˡ�"
	"���Ϸ��δ�磬ٲȻ��һλ�������\n");
	set("title", "����ɽ��ׯ��");
	set("gender", "����");
	set("age", 35);

	set_skill("cuff", 140);
	set_skill("strike", 140);
	set_skill("shentuo-zhang", 140);
	set_skill("lingshe-quan", 140);
	set_skill("dodge", 140);
	set_skill("chanchubu", 140);
	set_skill("parry",140);
	set_skill("force", 140);
	set_skill("hamagong", 140);
	set_skill("lingshe-zhang",140);
	set_skill("staff",140);
	set_skill("strike",140);
	set_skill("poison",140);
	set_skill("training",140);
	map_skill("cuff","lingshe-quan");
	map_skill("strike","shentuo-zhang");
	map_skill("dodge","chanchubu");
	map_skill("parry", "lingshe-zhang");
	map_skill("staff","lingshe-zhang");
	map_skill("force","hamagong");
	prepare_skill("cuff","lingshe-quan");
	prepare_skill("strike","shentuo-zhang");

	set("str", 23);
	set("int", 23);
	set("con", 24);
	set("dex", 28);

	set("max_qi", 1500);
	set("max_jing", 600);
	set("neili", 2500);
	set("max_neili", 2500);
	set("jiali", 40);
	set("combat_exp", 900000);

	set("attitude", "peaceful");
	set("shen_type", -1);

	create_family("����ɽ", 2 , "����");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
		(: auto_perform :),
	}) );

	set("inquiry", ([
		"ŷ����" : "�������常��",
		"��ʬ��" : "��ֻ��һ�ݻ�ʬ�ۣ����ܸ��㡣������Ҫ�Ǹ���һ��ʬ�壬�ҿ��Ը�����Щ��",
		"��" : (: ask_job :),
		"job" : (: ask_job :),
	]));

	setup();
	set_temp("job_pos",20);
	carry_object("/d/xingxiu/npc/obj/shezhang")->wield();
	carry_object("/d/xingxiu/obj/wcloth")->wear();
	carry_object("/d/xingxiu/obj/diaoqiu")->wear();
}


void attempt_apprentice(object ob)
{
		mapping fam;

		if( !mapp(fam = ob->query("family")) || fam["family_name"] != "����ɽ")
	{
		command ("say " + RANK_D->query_respect(ob) +
			"��ȥ��ɽׯ��ʦ���˷��������´���Ӱɡ�");
		return;
	}
	if ((int)ob->query_skill("hamagong", 1) < 30) {
		command("say ���ǰ���ɽׯ�ľ������常�����ĸ�󡹦��");
		command("say " + RANK_D->query_respect(ob) + "�Ƿ�Ӧ���ڸ�󡹦�϶��µ㹦��");
		return;
		}
	command("say �ðɣ��������ɽׯ������ׯ��ʦ�ɡ�");
	command("recruit " + ob->query("id"));
	ob->set("title","����ɽׯ��ʦ");
	return;
}

void init()
{
		object ob;
		::init();
		if (interactive(ob = this_player()) && !is_fighting()) {
			 remove_call_out("greeting");
			 call_out("greeting", 1, ob);
		}
}

void greeting(object me)
{
        int sxds, hand;
		sxds = me->query_skill("shexing-diaoshou",1);
        hand = me->query_skill("hand",1);
 
		if( me->query("family/family_name") == "����ɽ"
		&& !me->query("baituo_updated") ) {
			 me->set_skill("cuff", hand);
			 me->set_skill("lingshe-quan", sxds);
			 me->delete_skill("hand");
			 me->delete_skill("shexing-diaoshou");
			 me->set("baituo_updated",1);
		}
		return;
}

string ask_job()
{
	mapping job_stat;
	object ob2;
	object ob = this_player();
	object me = this_object();
	object guaishe,staff,here=environment(me);
	int good_skill;

	job_stat = ob->query_temp("baituo/feeding");

	if ( ob->query("family/family_name") != "����ɽ" )
		return RANK_D->query_rude(ob)+"Ī�Ǳ������ģ�\n";

	if( ob->is_busy() ){
		command("hmm "+ob->query("id"));
		return "�㻹��æ�Ÿɱ�����أ�\n";
	}

	if( job_stat ){
		command("hmm "+ob->query("id"));
		return "�㻹û�������!\n";
	}

/*
	if( ob->query("combat_exp") < 100 ) {
		command("hmm");
		return "Сë���Ը���ȥ������үæ���ء�\n";
	}
*/

	if( ob->query_skill("training") < 10 && random(4)!=0 ) {
		return "���ѱ����̫�ͣ������ֻ������ȥ�ɡ�\n";
	}


	ob->start_busy(random(4));
	good_skill = (int)( pow(ob->query("combat_exp")*10,0.33333) * 0.7 ) * 3/2 ;

	if( ob->query("combat_exp") > 20000 && ( ob->query_skill("force") < good_skill ) && random(15) > 0 ) {
		command("say ��ȥ�ú���ϰһ�¸�󡹦�ɣ�");
		return "��󡹦�Ǳ��ɵĶ��ž���������֮��һ�����԰ﱾ��ү��ץ������Ů����\n";
		}

	if( ob->query("combat_exp") > 5000 && 
	ob->query("max_neili") < ob->query_skill("force") * 7 && random(5) > 0 ) {
		command("say ������������ȥ�úô���һ�°ɣ�");
		return "����Խ�ߣ���󡹦��������Խ�󣬺ٺڣ�����ü��һ��Ҳ������\n";
		}



	if ( me->query_temp("job_pos") == 0 ) {
		if(random(8)==1)
		me->set_temp("job_pos",1);
		return "����ûʲô�£����Ը����ε�ȥ�ɡ�\n";
	}

	me->add_temp("job_pos", -1);

	command("nod");
	command("say �ã���������һֻ�涾�Ĺ��ߣ�"+ob->query("name")+"����ȥ�úõ�����");
	command("say ����߳����ࡢ����Ѫ��Խ����ν�������ɵĸ��ֵ���ѪԽ���������ߡ�");
	command("hehe");
	command("say ���Ա������ᣬ�ͻ�ԹԵ������������Ϊ�����������ı�����");


	guaishe = present("guai she",me );
	if(guaishe)destruct(guaishe);
	guaishe = present("guai she",me );
	if(guaishe)destruct(guaishe);
	ob2 = new("/d/xingxiu/npc/guaishe");
	ob2->move(me);
	ob2->set_owner(ob);
	ob->set_temp("baituo/feeding",1);
	command("give guai she to "+ob->query("id"));
	guaishe = present("guai she",me );
	if(guaishe)command("drop guai she");

	staff = present("guai shezhang",here);
	if(!staff)staff=present("guai shezhang",ob);
	if(staff)destruct(staff);
	staff = new("/clone/weapon/gshezhan");
	staff->move(me);
	command("give guai shezhang to "+ob->query("id"));
	guaishe = present("guai shezhang",me );
	if(guaishe)command("drop guai shezhang");

	return "ǧ���Ū���ˣ�\n";
}

int accept_object(object me, object obj)
{
	object hsf, ob = this_player();

	if (obj->query("id")=="corpse")
	{
		if (!me->query("family") || me->query("family/family_name")!= "����ɽ"){
			command("say ��Ҫ�Ҹ�����ʬ���ɣ�\n");
			return 0;
		}
		if (me->query("family/master_name") != "ŷ����" &&
			me->query("family/master_name") != "ŷ����") {
			command("say �㻹�������ù���ɡ�\n");
			return 0;
		}
		if (me->query_temp("huashifen")) {
			 command("say ��ʬ���������Ե�ҩ�ﲻҪ�õù��ࡣ\n");
			return 0;
		 }

		message_vision("$N��" + obj->name() + "���ڵ��ϣ��ӻ����ͳ�һ�ݻ�ʬ���������档\n",this_object());
		message_vision("Ƭ��֮�䣬" + obj->name() + "����һ̲��ˮ����ˮ���˺����һ�ѷ���ӫӫ�Ļƹ�ķ�ĩ��\n" ,obj);
		message_vision("$N������һ�����ڻ��У�����Ľ���$n��\n",this_object(),me);
		command("say ����԰ѻ�ʬ�۵���ʬ���ϣ��ɼ��̽����ڻ�����");
		command("say ��Ҳ���԰���Ϳ�ڱ����ϸ�����װ���ˣ��������������˿ڣ����������ˡ�");
		command("hehe ouyang ke");

		hsf = new(DRUG_D("huashi"));
		hsf->set_amount(10);
		hsf->move(me);
		me->set_temp("huashifen",1);
		return 1;
	}

		command( "say "+obj->name()+"?");

		if (obj->query("id") == "guai she") {
			call_out("destroy_dest", 1, obj, ob);
			return 1;
		}

		if ( obj->query("id") == "guai shezhang") {
			if ( ob->query("family/family_name") == "����ɽ" ) {
				if( obj->query("snake")>0 )
					call_out("reward_dest", 1, obj, ob);
				else
					call_out("destroy_staff", 1, obj, ob);
			}
			else {
				call_out("thank_dest", 1, obj, ob);
			}
			return 1;
		}

		command( "hmm" );
		command( "say ������ⶫ����ʲ�᣿" );

		return 0;
}

void reward_dest(object obj,object ob)
{
	command( "pat "+ob->query("id"));
	command( "say "+ob->query("name")+"�ɵĻ�������������ɻ��������үһ��������ģ�\n");
	if(ob->query("gender") == "Ů��" )
		command( "kiss1 " + ob->query("id") );

	if(ob->query_temp("baituo/feeding",1) )
	{
		ob->delete_temp("baituo/feeding");
		add_temp("job_pos", 1);
	}
	destruct(obj);
}


void destroy_staff(object obj,object ob)
{
	command( "hmm" );
	command( "kick "+ob->query("id") );
	command( "say ��ô�����������ң����أ�С����ү������һ���ȣ�" );
	command( "angry" );

	destruct(obj);
}

void destroy_dest(object obj,object ob)
{
	command( "hmm" );
	command( "kick "+ob->query("id") );
	command( "say ��ô�����������ң�Ӧ��ι����������ٽ����ҡ�С����ү��������߳ԣ�" );
	command( "angry" );

	if(ob->query_temp("baituo/feeding",1) )
	{
		ob->delete_temp("baituo/feeding");
		add_temp("job_pos", 1);
	}
	destruct(obj);
}


void thank_dest(object obj,object ob)
{
	command( "ah");
	command( "jump");
	command( "say ����ү�����ȣ���л����\n");
	destruct(obj);
}


#include "/kungfu/class/baituo/auto_perform.h"