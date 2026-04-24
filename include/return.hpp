#pragma once

#include <string>

enum class ResultCode {
    Ok,
    Error
};

struct Result {
	ResultCode	code;
	std::string	message;

	bool isOk() const { return code == ResultCode::Ok; }

	static Result ok() { return {ResultCode::Ok, ""}; }
	static Result error(std::string msg) { return {ResultCode::Error, std::move(msg)}; }
};
