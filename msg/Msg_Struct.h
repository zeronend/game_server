/**
 * struct Msg_Struct description
 *
 * [This file was auto-generated. PLEASE DONT EDIT]
 *
 * @copyright urentech.com
 *
 */



#ifndef MSG_STRUCT_H_
#define MSG_STRUCT_H_

#include <cstring>
#include "Block_Buffer.h"
/*

	角色信息
*/
struct Role_Info {

	int64_t role_id;

	std::string account;

	std::string role_name;

	uint8_t career;

	uint8_t gender;

	uint16_t level;

	Role_Info(void);

	void serialize(Block_Buffer & w) const;

	int deserialize(Block_Buffer & r);

	void reset(void);
};
/*

	物品基本信息

	备注：

	EQUIP_INDEX = 10000,

	PACKAGE_INDEX = EQUIP_INDEX + INDEX_GAP,
*/
struct Item_Basic_Info {

	uint32_t index;/*位置标识符*/

	uint32_t id;/*道具id（图标id整合到此id）*/

	int32_t amount;/*总量*/

	uint8_t bind;/*是否绑定（0）不绑，（2）已绑 其他值非法*/

	Item_Basic_Info(void);

	void serialize(Block_Buffer & w) const;

	int deserialize(Block_Buffer & r);

	void reset(void);
};
struct Money_Info {

	int32_t bind_copper;/*绑定铜钱*/

	int32_t copper;/*铜钱*/

	int32_t coupon;/*礼卷*/

	int32_t gold;/*元宝*/

	Money_Info(void);

	void serialize(Block_Buffer & w) const;

	int deserialize(Block_Buffer & r);

	void reset(void);
};
struct Mail_Detail {

	int32_t mail_id; //邮件id

	int8_t pickup; //是否收取过附件

	int32_t send_time; //发邮件时间

	int32_t sender_type; //发件人类型

	int64_t sender_id; //发件人id

	std::string sender_name; //发件人名字

	std::string mail_title; //邮件标题

	std::string mail_content; //邮件内容

	Money_Info money_info; //金钱信息

	std::vector<Item_Basic_Info> item_vector; //物品信息

	Mail_Detail(void);

	void serialize(Block_Buffer & w) const;

	int deserialize(Block_Buffer & r);

	void reset(void);
};


#endif
