#pragma once

#include <string>

#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"

namespace eeGames
{
	class Request
	{
	private:
		uint16_t _m_priority; // lower value has highest priority
		uint8_t _m_refCount;
		std::string _m_dependency, _m_id;
		RequestType _m_requestType;

		// for storing data
		DataType _m_dataType;
		std::string _m_targetName;
		byte *_m_data;
	public:
		Request(const std::string &_p_id, uint16_t _p_priority, RequestType _p_requestType) : _m_id(_p_id), _m_requestType(_p_requestType), 
			_m_priority(_p_priority), _m_dependency(""), _m_dataType(DataType::NONE), _m_data(nullptr), _m_refCount(1) {}
		Request(const std::string &_p_id, const std::string &_p_dependency, RequestType _p_requestType) : _m_id(_p_id), _m_requestType(_p_requestType), 
			_m_priority(-1), _m_dependency(_p_dependency), _m_dataType(DataType::NONE), _m_data(nullptr), _m_refCount(1) {}

		// TODO: Certain input methods do not require a name for the string (string input)
		void addData(void *_p_data, DataType _p_dataType);
		void addData(byte *_p_data)
		{
			_m_data = _p_data;
		}
		void addTargetName(const std::string &_p_name)
		{
			_m_targetName = _p_name;
		}

		int getInt(bool *t);
		int getInt();
		float getFloat(bool *t);
		float getFloat();
		double getDouble(bool *t);
		double getDouble();
		bool getBool(bool *t);
		bool getBool();
		std::string getString(bool *t);
		std::string getString();

		RequestType getRequest() const
		{
			return _m_requestType;
		}
		uint16_t getPriority() const
		{
			return _m_priority;
		}
		const std::string &getDependency() const
		{
			return _m_dependency;
		}
		const std::string &getID() const
		{
			return _m_id;
		}

		DataType getDataType() const
		{
			return _m_dataType;
		}
		const std::string &getTargetName() const
		{
			return _m_targetName;
		}
		byte *getData() // can't gaurentee data will remain unchanged
		{
			return _m_data;
		}

		// angelscript
		void AddRef()
		{
			_m_refCount++;
		}
		void ReleaseRef()
		{
			if (--_m_refCount == 0)
				delete this;
		}
	};

	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, int *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, float *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, double *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, bool *d2);
	extern inline Request *create_request(const std::string &i, uint16_t p, RequestType rt, const std::string &d1, std::string &d2);

	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, int *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, float *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, double *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, bool *d2);
	extern inline Request *create_request(const std::string &i, const std::string &dep, RequestType rt, const std::string &d1, std::string &d2);
}
