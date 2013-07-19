#include "logging.h"

int main(int argc, char** argv) {
	logging_reset_timer();

	logging_log_message(STATUS, "Random status message number %u", 5);

	return 0;
}
