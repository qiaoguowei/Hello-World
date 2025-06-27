#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>

using namespace std;

/* struct inotify_event
 * {
 *     int wd;  //监控描述符 	
 *     uint32_t mask; //事件掩码类型
 *     uint32_t cookie; //关联的相关事件
 *     uint32_t len; //name字段的长度
 *     char name[]; //引发该事件的文件或目录名的C字符串
 * };
 *
 * 事件掩码			事件描述
 * IN_ACCESS		访问文件
 * IN_CLOSE_NOWRITE	关闭打开时为设置不可写的文件
 * IN_DELETE_SELF	删除监控中的文件或目录本身
 * IN_MOVE_FROM		移出或重命名目录中包含的文件
 * IN_ATTRIB		文件属性更改(权限，所有权等)
 * IN_CREATE		创建文件或目录
 * IN_MODIFY		修改文件
 * IN_MOVE_TO		移入或重命名目录中包含的文件
 * IN_CLOSE_WRITE	关闭打开时设置为可写的文件
 * IN_DELETE		删除文件或目录
 * IN_MOVE_SELF		移动监控中的文件或目录本身
 * IN_OPEN			打开文件或目录
 *
 * */

int main()
{
	int eventfd = inotify_init();
	if (eventfd < 0)
	{
		cout << "failed to create inotify instance" << endl;
		return -1;
	}

	int wd = inotify_add_watch(eventfd, "/home/qgw/my_github/Hello-World/cpp/C", IN_CREATE | IN_DELETE | IN_MODIFY | IN_CLOSE_WRITE);
	if (wd < 0)
	{
		cout << "failed to add watch." << endl;
		return -1;
	}

	cout << "start to watch directory /home/qgw" << endl;
	char buffer[4096];

	while(1)
	{
		ssize_t len = read(eventfd, buffer, sizeof(buffer));
		if (len == -1)
		{
			cout << "End watch" << endl;
			break;
		}

		ssize_t i = 0;
		while (i < len)
		{
			struct inotify_event *event = (struct inotify_event *)(buffer + i);
			if (event->mask == IN_CREATE)
				cout << "IN_CREATE: " << event->name << endl;
			if (event->mask == IN_DELETE)
				cout << "IN_DELETE: " << event->name << endl;
			if (event->mask == IN_MODIFY)
				cout << "IN_MODIFY: " << event->name << endl;
			if (event->mask == IN_CLOSE_WRITE)
				cout << "IN_CLOSE_WRITE: " << event->name << endl;

			i += event->len + sizeof(struct inotify_event);
		}
	}

	return 0;
}









