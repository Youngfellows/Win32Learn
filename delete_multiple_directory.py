# coding=utf-8

import os
import shutil
import os.path


class DeleteDirectory(object):
    """
    删除当前路径下指定文件名称的目录工具类
    """

    def __init__(self):
        object.__init__(self)
        self.directory_name_build = "build"  # 需要删除的build目录名称
        self.directory_name_x64 = "x64"  # 需要删除的x64目录名称
        self.directory_name_x86 = "x86"  # 需要删除的x86目录名称
        self.directory_name_Debug = "Debug"  # 需要删除的Debug目录名称
        self.directory_name_Release = "Release"  # 需要删除的Release目录名称
        self.directory_name_dot_vs = ".vs"  # 需要删除的.vs目录名称

    def delete_directory(self):
        """
        删除当前路径下指定文件名称的目录
        :return:
        """
        path = os.getcwd()  # 返回当前工作目录
        dirs = os.listdir(path)  # 获取所有文件和文件夹
        print("path:{}".format(path))
        print("dirs:{}".format(dirs))

        # 输出所有文件和文件夹
        for file in dirs:
            # print(file)
            if os.path.isdir(file):
                if (file == self.directory_name_x64) or \
                        (file == self.directory_name_x86) or \
                        (file == self.directory_name_Debug) or \
                        (file == self.directory_name_Release) or \
                        (file == self.directory_name_dot_vs):
                    strfilepath = path + os.sep + file
                    print("1,目录: {}".format(strfilepath))
                    if os.path.isdir(strfilepath):
                        os.system('attrib -r ' + path + '\\*.* /s')  # 设置本文件夹可写
                        os.system('attrib -r ' + strfilepath + '\\*.* /s')  # 设置父文件夹可写
                        shutil.rmtree(strfilepath)  # 删除此文件夹
                        print("已删除目录: {}".format(strfilepath))
                else:
                    dir_path = path + os.sep + file
                    print("2,目录: {}".format(dir_path))
                    # 获得指定路径下的所有文件及文件夹下子文件的目录列表
                    for parent, dirnames, filenames in os.walk(dir_path):  # 遍历文件夹下面的所有文件夹
                        print("dirnames: {}".format(dirnames))
                        for dirname in dirnames:
                            strfilepath = parent + os.sep + dirname
                            if (dirname == self.directory_name_x64) or \
                                    (dirname == self.directory_name_x86) or \
                                    (dirname == self.directory_name_Debug) or \
                                    (dirname == self.directory_name_Release) or \
                                    (dirname == self.directory_name_dot_vs):

                                if os.path.isdir(strfilepath):
                                    os.system('attrib -r ' + parent + '\\*.* /s')  # 设置本文件夹可写
                                    os.system('attrib -r ' + strfilepath + '\\*.* /s')  # 设置父文件夹可写
                                    shutil.rmtree(strfilepath)  # 删除此文件夹
                                    print("已删除目录: {}".format(strfilepath))


if __name__ == "__main__":
    delete = DeleteDirectory()
    delete.delete_directory()
