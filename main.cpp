#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <array>

#include "ed25519/src/ed25519.h"

#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "common/base58.h"
#include "api/API.h"

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace api;

class ac
{
public:
	static std::string address(const char* sa)
	{
		std::vector<byte> evec;
		DecodeBase58(sa, evec);
		std::string dst(evec.size(), 0);
		// memcpy_s((void*)dst.c_str(), vec.size(), &(vec[0]), vec.size());
		memcpy((void*)dst.c_str(), &(evec[0]), evec.size());
		return dst;
	}

	template<typename T>
	static void copy(std::vector<byte>& src, T& val)
	{
		auto a = to_bytes(std::addressof(val));
		std::copy(std::begin(a), std::end(a), std::back_inserter(src));
	}
};

int main()
{
	std::shared_ptr<TSocket> socket = std::shared_ptr<TSocket>(new TSocket("127.0.0.1", 9090));
	std::shared_ptr<TTransport> transport = std::shared_ptr<TTransport>(new TBufferedTransport(socket));
	std::shared_ptr<TProtocol> protocol = std::shared_ptr<TProtocol>(new TBinaryProtocol(transport));
	std::shared_ptr<APIClient> api = std::shared_ptr<APIClient>(new APIClient(protocol));

	try
	{
		transport->open();
	}
	catch (...)
	{
		printf("thrift error: failed connect to node\n");
	}

	if (transport->isOpen())
	{
		std::cout << "Transport was opened" << std::endl;

		const char* ssa = "your address";
		general::Address sa = ac::address(ssa);

		WalletBalanceGetResult bg_res;
		PoolHash ph;
		TransactionFlowResult tr_res;
		try
		{
			api->WalletBalanceGet(bg_res, sa);
		}
		catch (...)
		{
			return 1;
		}

		bg_res.printTo(std::cout);
		std::cout << std::endl << std::endl;

		transport->close();
	}
}

