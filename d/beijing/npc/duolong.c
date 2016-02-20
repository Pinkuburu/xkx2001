//Cracked by Roath

inherit NPC;
string ask_job();
string ask_suicong();
string ask_yaopai();
int do_ling(string);

#include "/d/beijing/beijing_defs.h"
#include "/d/beijing/job_info.h"
void set_shiwei_status(int);

void create()
{
    set_name("��¡", ({
	    "duolong", "duo",
    }));
    set("title", "�����ܹ�");
    set("long",
	"��Ϊ�����ܹܣ���¡���ܻ������ء�\n"
	"���־������񶼴���������ɡ�\n"
    );


    set("gender", "����");
    set("age", 35);
    setup();

    set_shiwei_status(180);

    set("inquiry", ([
	"job" : (: ask_job :),
	"����" : (: ask_job :),
	"����" : "����㵽����ȥ��������ɡ�",
	"promote" : "����㵽����ȥ��������ɡ�",
	"����" : "����㵽����ȥ��������ɡ�",
	"���" : (: ask_suicong :),
	"suicong" : (: ask_suicong :),
	"here" : "����������Ӫ������������",
	"����" : (: ask_yaopai :),
	"yaopai" : (: ask_yaopai :),
    ]));
}

void init()
{
    add_action("do_ling", "ling");
}

int sync_mizheng(object player)
{
    object mizheng;

    // fix test players
    mizheng = HELPER->find_mizheng();
    if (mizheng->player_rank(player->query("id")) == -1) {
	message_vision("$N�ɻ�Ŀ���$nһ�ۣ�����ô��������ͷ�εģ�\n",
	    this_object(), player);
	mizheng->normalize(player);
        return 1;
    }
    return 0;
}

string ask_yaopai ()
{
    object player = this_player(), me = this_object();
    object *inv, yaopai;
    int i;

    if (! IS_SHIWEI(player)) 
	return "���ֲ���������Ҫʲô���ƣ�";

    if (sync_mizheng(player)) return "�����µ��������Ƕ�ȥ�Ǽǰɡ�";

    inv = all_inventory(player);
    for (i=0; i<sizeof(inv)-1; i++){
	if (base_name(inv[i]) == "/d/beijing/obj/yaopai") 
	    return "�㲻������������";
    }
    yaopai = new ("/d/beijing/obj/yaopai");
    yaopai->move(player);
    message_vision("$N��$nһ���������ơ�\n", me, player);
    return "С�ĵ㣬���ϸ㶪�ˡ�";
}

string ask_job()
{
    object player = this_player(), me = this_object();
    int i, shichen=HELPER->shichen();

    if (!IS_SHIWEI(player)) 
        return "���ȵ�����Ͷ���ɡ�";
    if (sync_mizheng(player)) return "�����µ��������Ƕ�ȥ�Ǽǰɡ�";

    if (player->query_temp("current_job")) {
	if (SHIWEI_LEVEL(player)<4) {
	    return "�Ҳ��Ǹ���������ȥ"+
		    player->query_temp("current_job")+"���Űɡ�";
	}
  	return "�Ҳ��Ǹ���������?";
    }

    switch (SHIWEI_LEVEL(player)) {
    case 0:	// first level
	if (HELPER->is_sunrise() < 0) 
	    return "���ڻ�û���㵱���ʱ���ء�";
	if (HELPER->is_sunrise() > 0) 
	    return "������î��ʱ���Ѿ����ˣ������������ɡ�";
	i = random(sizeof(outer_gate_name));
	player->set_temp("current_job", outer_gate_name[i]);
	return "���ȥ"+outer_gate_name[i]+"���� (guard) �ɡ�";
    case 1:	// second level
	if (HELPER->is_sunset() < 0) 
	    return "�컹�����أ��Ȼ���������Ϸ����";
	if (HELPER->is_sunset() > 0) 
	    return "�춼�����������������˵�ɡ�";
	i = random(sizeof(outer_gate_name));
	player->set_temp("current_job", outer_gate_name[i]);
	return "���ȥ"+outer_gate_name[i]+"���� (guard) �ɡ�";
    case 2:	// third level
	if (HELPER->is_sunrise() < 0) 
	return "���ڻ�û���㵱���ʱ���ء�";
	if (HELPER->is_sunrise() > 0) 
	    return "������î��ʱ���Ѿ����ˣ������������ɡ�";
	i = random(sizeof(inner_gate_name));
	player->set_temp("current_job", inner_gate_name[i]);
	return "���ȥ"+inner_gate_name[i]+"���� (guard) �ɡ�";
    case 3:	// fourth level
	if (HELPER->is_sunset() < 0) 
	    return "�컹�����أ��Ȼ���������Ϸ����";
	if (HELPER->is_sunset() > 0) 
	    return "�춼�����������������˵�ɡ�";
	i = random(sizeof(inner_gate_name));
	player->set_temp("current_job", inner_gate_name[i]);
	return "���ȥ"+inner_gate_name[i]+"���� (guard) �ɡ�";
    default:
	return "����û���������";
    }
}

string ask_suicong()
{
    return "���ֻ��"+HELPER->rank_name(3)+"���ϵ��������С�\n"+
	"Ҫ����(ling)����أ�����������������ɵĶ��У����Լ����ɡ�\n";
}

int do_ling(string menpai)
{
    object player = this_player();
    object me = this_object(), suicong;
    int rank = SHIWEI_LEVEL(player);
    int suicong_num = player->query("suicong_num");
    string cmenpai;

    if (! IS_SHIWEI(player))
	return notify_fail("����ȥ����Ͷ���ɡ�\n");
    if (sync_mizheng(player)) 
	return notify_fail("�����µ��������Ƕ�ȥ�Ǽǰɡ�\n");
    if (HELPER->suicong_max(rank) == 0) 
	return notify_fail("��ļ��𲻹�����ӵġ�\n");
    if (suicong_num >= HELPER->suicong_max(rank)) 
	return notify_fail("���Ѿ���"+CHINESE_D->chinese_number(suicong_num)+
		"������ˡ�\n");

    if (! menpai || menpai == "")
	return notify_fail("��Ҫ��ʲô���ɵ���ӣ�\n");

    switch (menpai) {
        case "��ɽ��":
	case "��ɽ":
	    menpai = "huashan";
        case "huashan":
	    cmenpai =  "��ɽ��";
	    break;

        case "����":
	case "������":
	    menpai = "emei";
        case "emei":
	    cmenpai =  "������";
	    break;

 	case "�䵱":
	case "�䵱��":
	    menpai = "wudang";
        case "wudang":
	    cmenpai =  "�䵱��";
	    break;

	case "����":
	case "������":
	    menpai = "shaolin";
        case "shaolin":
	    cmenpai =  "������";
	    break;

	case "ؤ��":
	    menpai = "gaibang";
        case "gaibang":
	    cmenpai =  "ؤ��";
	    break;

	case "����":
	case "������":
	    menpai = "xingxiu";
        case "xingxiu":
	    cmenpai =  "����";
	    break;

	case "ѩɽ":
	case "ѩɽ��":
	case "Ѫ��":
	case "Ѫ����":
	    menpai = "xueshan";
        case "xueshan":
	    cmenpai =  "ѩɽ��";
	    break;

  	case "�һ�":
	case "�һ���":
	    menpai = "taohua";
        case "taohua":
	    cmenpai =  "�һ���";
	    break;

	case "����":
	case "����ɽׯ":
	    menpai = "baituo";
        case "baituo":
	    cmenpai =  "����ɽׯ";
	    break;

        case "����":
	case "��������":
	case "dali":
	    return notify_fail("�������ϵļҳ���ô�������ǵ�����أ�\n");

  	case "����":
	case "������":
	case "shenlong":
	    return notify_fail("�������ڹٸ����˾�׽�á���û����ɣ�\n");

        default:
                return notify_fail("��Ҫ��ʲô���ɵ����������\n");
                break;
        }
    suicong_num ++;
    player->set("suicong_num", suicong_num);
    suicong = new("/clone/npc/suicong.c");
    suicong->new_master(player, suicong_num, menpai);
    suicong->move(environment(player));
    suicong->set_leader(player);
    player->save();
    message_vision("$N��$n˵�����¹���Ҫһ��"+cmenpai+"����ӡ�\n",
		player, me);
    message_vision("$N������$n�ļ��Ц�����úã�û���⣬���˰���\n", 
		me, player);
    message_vision("$N�첽���˹�������$n���������ү�𰲡�\n",
		suicong, player);
    return 1;
}

#include "/d/beijing/autok.h"