default:
	rm -r /opt/desulogd
	mkdir -p /opt/desulogd
	touch /opt/desulogd/desulog.log
	touch /opt/desulogd/pidlist.txt
	echo "{\"list_of_signals\": {\"SIGSTOP\": true,\"SIGCONT\": true,\"SIGHUP\": true,\"SIGINT\": true,\"SIGTERM\": true,\"SIGKILL\": true,\"SIGUSR1\": true,\"SIGUSR2\": true},\"log_file_path\": \"/opt/desulogd/desulog.log\"}" >> /opt/desulogd/config.json
	g++ src/main.cpp src/cpp/secondaryFunctions.cpp src/cpp/controllers.cpp -o /opt/desulogd/desulogd
