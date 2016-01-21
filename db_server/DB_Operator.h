// -*- C++ -*-
/*
 * DB_Operator.h
 *
 *  Created on: Dec 29, 2015
 *      Author: zhangyalei
 */

#ifndef DB_OPERATOR_H_
#define DB_OPERATOR_H_

#include "Public_Struct.h"
#include "Object_Pool.h"
#include "boost/unordered_map.hpp"
#include "json/json.h"

namespace mongo {
class DBClientConnection;
class BSONObj;
class BSONObjBuilder;
}

using namespace mongo;

class DB_Operator {
public:
	typedef boost::unordered_map<int64_t, DBClientConnection *> Connection_Map;
	typedef Object_Pool<DBClientConnection, Thread_Mutex> Connection_Pool;

	static DB_Operator *instance(void);
	mongo::DBClientConnection &connection(void);

	int init(void);
	int create_index(void);
	int load_db_cache(int cid);

	inline int64_t get_agent_and_server_prefix(void);
	inline int64_t get_min_server_diff_key(void);
	inline int64_t get_max_server_diff_key(void);

	role_id_t create_init_player(Game_Player_Info &player_info);
	role_id_t get_role_id(const std::string &account, const int agent_num, const int server_num);
	int get_role_name_by_id(role_id_t role_id, std::string &name);
	int get_account_by_id(role_id_t role_id, std::string &account);
	int has_role_by_account(std::string &account, const int agent_num, const int server_num);
	int has_role_by_id(role_id_t role_id);

	int save_player_info(Game_Player_Info &player_info);
	int load_player_info(Game_Player_Info &player_info);

	int load_bag_info(Bag_Info &bag_info);
	int save_bag_info(Bag_Info &bag_info);
	int load_item_detail(const mongo::BSONObj &obj, Item_Info &item);
	int save_item_detail(const Item_Info &item, mongo::BSONObj &obj);

	int load_mail_info(Mail_Info &mail_info);
	int save_mail_info(Mail_Info &mail_info);

private:
	DB_Operator(void);
	virtual ~DB_Operator(void);
	DB_Operator(const DB_Operator &);
	const DB_Operator &operator=(const DB_Operator &);

private:
	static DB_Operator *instance_;
	Connection_Pool connection_pool_;
	Connection_Map connection_map_;
	MUTEX connection_map_lock_;

	int agent_num_; /// 代理编号
	int server_num_; /// 服编号
	Int_IntSet_Map server_map_;			/// 代理-服编号
	int64_t agent_and_server_prefix_;	/// 根据服编号跟代理编号生成的前缀
	int64_t min_server_diff_key_;
	int64_t max_server_diff_key_;
};

inline int64_t DB_Operator::get_agent_and_server_prefix(void) {
	return agent_and_server_prefix_;
}

inline int64_t DB_Operator::get_min_server_diff_key(void) {
	return min_server_diff_key_;
}

inline int64_t DB_Operator::get_max_server_diff_key(void) {
	return max_server_diff_key_;
}

#define CACHED_INSTANCE			DB_Operator::instance()
#define CACHED_CONNECTION		CACHED_INSTANCE->connection()

#endif /* DB_OPERATOR_H_ */
