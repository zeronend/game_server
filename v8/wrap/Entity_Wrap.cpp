/*
 * Entity_Wrap.cpp
 *
 *  Created on: 2016年7月25日
 *      Author: lijunliang
 */

#include "Entity_Wrap.h"
#include "Player_Wrap.h"
#include "Game_Manager.h"
#include "Master_Manager.h"

extern Global<ObjectTemplate> _g_game_player_template;
extern Global<ObjectTemplate> _g_master_player_template;

Local<Object> wrap_game_player(Isolate* isolate, Game_Player *player) {
	EscapableHandleScope handle_scope(isolate);

	Local<ObjectTemplate> localTemplate = Local<ObjectTemplate>::New(isolate, _g_game_player_template);
	localTemplate->SetInternalFieldCount(1);
	Local<External> player_ptr = External::New(isolate, player);
	//将指针存在V8对象内部
	Local<Object> player_obj = localTemplate->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
	player_obj->SetInternalField(0, player_ptr);

	return handle_scope.Escape(player_obj);
}

Game_Player *unwrap_game_player(Local<Object> obj) {
	Local<External> field = Local<External>::Cast(obj->GetInternalField(0));
	void* ptr = field->Value();
	return static_cast<Game_Player*>(ptr);
}

void get_game_player_save_data_buffer(const FunctionCallbackInfo<Value>& args) {
	Game_Player *player = unwrap_game_player(args.Holder());
	if (!player) {
		args.GetReturnValue().SetNull();
		return;
	}

	Block_Buffer *buf = player->save_player_data_buffer();
	if (buf) {
		buf->reset();
		args.GetReturnValue().Set(wrap_buffer(args.GetIsolate(), buf));
	} else {
		//设置对象为空
		args.GetReturnValue().SetNull();
	}
}

void game_player_respond_success_result(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
		LOG_ERROR("respond_success_result args error, length: %d\n", args.Length());
		return;
	}

	Game_Player *player = unwrap_game_player(args.Holder());
	if (!player) {
		return;
	}

	int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	Block_Buffer *buf = unwrap_buffer(args[1]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
	player->respond_success_result(msg_id, buf);
}

void game_player_respond_error_result(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
		LOG_ERROR("respond_error_result args error, length: %d\n", args.Length());
		return;
	}

	Game_Player *player = unwrap_game_player(args.Holder());
	if (!player) {
		return;
	}

	int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	int error_code = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	player->respond_error_result(msg_id, error_code);
}

void sync_data_to_master(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
			LOG_ERROR("sync_data_to_game args error, length: %d\n", args.Length());
			return;
	}

	Game_Player *player = unwrap_game_player(args.Holder());
	if (!player) {
		return;
	}

	int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	Block_Buffer *buf = unwrap_buffer(args[1]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
	player->sync_data_to_master(msg_id, buf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Local<Object> wrap_master_player(Isolate* isolate, Master_Player *player) {
	EscapableHandleScope handle_scope(isolate);

	Local<ObjectTemplate> localTemplate = Local<ObjectTemplate>::New(isolate, _g_master_player_template);
	localTemplate->SetInternalFieldCount(1);
	Local<External> player_ptr = External::New(isolate, player);
	//将指针存在V8对象内部
	Local<Object> player_obj = localTemplate->NewInstance(isolate->GetCurrentContext()).ToLocalChecked();
	player_obj->SetInternalField(0, player_ptr);

	return handle_scope.Escape(player_obj);
}

Master_Player *unwrap_master_player(Local<Object> obj) {
	Local<External> field = Local<External>::Cast(obj->GetInternalField(0));
	void* ptr = field->Value();
	return static_cast<Master_Player*>(ptr);
}

void get_master_player_save_data_buffer(const FunctionCallbackInfo<Value>& args) {
	Master_Player *player = unwrap_master_player(args.Holder());
	if (!player) {
		args.GetReturnValue().SetNull();
		return;
	}

	Block_Buffer *buf = player->save_player_data_buffer();
	if (buf) {
		buf->reset();
		args.GetReturnValue().Set(wrap_buffer(args.GetIsolate(), buf));
	} else {
		//设置对象为空
		args.GetReturnValue().SetNull();
	}
}

void master_player_respond_success_result(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
		LOG_ERROR("respond_success_result args error, length: %d\n", args.Length());
		return;
	}

	Master_Player *player = unwrap_master_player(args.Holder());
	if (!player) {
		return;
	}

	int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	Block_Buffer *buf = unwrap_buffer(args[1]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
	player->respond_success_result(msg_id, buf);
}

void master_player_respond_error_result(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
		LOG_ERROR("respond_error_result args error, length: %d\n", args.Length());
		return;
	}

	Master_Player *player = unwrap_master_player(args.Holder());
	if (!player) {
		return;
	}

	int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	int error_code = args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
	player->respond_error_result(msg_id, error_code);
}

void sync_data_to_game(const FunctionCallbackInfo<Value>& args) {
	if (args.Length() != 2) {
			LOG_ERROR("sync_data_to_game args error, length: %d\n", args.Length());
			return;
		}

		Master_Player *player = unwrap_master_player(args.Holder());
		if (!player) {
			return;
		}

		int msg_id = args[0]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(0);
		Block_Buffer *buf = unwrap_buffer(args[1]->ToObject(args.GetIsolate()->GetCurrentContext()).ToLocalChecked());
		player->sync_data_to_game(msg_id, buf);
}