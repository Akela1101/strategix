#include <strx/kernel/Kernel.h>

INITIALIZE_EASYLOGGINGPP

int main()
{
	using namespace strx;
	
	nya::init_logs("config/log.conf");
	
	Kernel::Run("config/strategix.json");
	//Kernel::PrintInfo();
	
	Kernel::Finish();
}