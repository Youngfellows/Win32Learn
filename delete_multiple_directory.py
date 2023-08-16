# coding=utf-8

import os
import shutil
import os.path
import re


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
        self.directory_name_ipch = "ipch"  # 需要删除的ipch目录名称
        self.suffix_sdf = ".sdf"  # 需要删除的.sdf文件名称

    def delete_directory_or_file(self):
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
            print(file)
            if os.path.isdir(file):
                if (file == self.directory_name_x64) or \
                        (file == self.directory_name_x86) or \
                        (file == self.directory_name_Debug) or \
                        (file == self.directory_name_Release) or \
                        (file == self.directory_name_ipch) or \
                        (file == self.directory_name_dot_vs):
                    strfilepath = path + os.sep + file
                    # print("1,目录: {}".format(strfilepath))
                    if os.path.isdir(strfilepath):
                        os.system('attrib -r ' + path + '\\*.* /s')  # 设置本文件夹可写
                        os.system('attrib -r ' + strfilepath + '\\*.* /s')  # 设置父文件夹可写
                        shutil.rmtree(strfilepath)  # 删除此文件夹
                        print("已删除目录: {}".format(strfilepath))
                else:
                    dir_path = path + os.sep + file
                    # print("2,目录: {}".format(dir_path))
                    # 获得指定路径下的所有文件及文件夹下子文件的目录列表
                    for parent, dirnames, filenames in os.walk(dir_path):  # 遍历文件夹下面的所有文件夹
                        # print("dirnames: {}".format(dirnames))
                        # print("filenames: {}".format(filenames))

                        # 1.删除指定文件
                        for filename in filenames:
                            strfilepath = parent + os.sep + filename
                            print(strfilepath)
                            self.delete_file(strfilepath)

                        # 2.删除指定目录
                        for dirname in dirnames:
                            strfilepath = parent + os.sep + dirname
                            if (dirname == self.directory_name_x64) or \
                                    (dirname == self.directory_name_x86) or \
                                    (dirname == self.directory_name_Debug) or \
                                    (dirname == self.directory_name_Release) or \
                                    (dirname == self.directory_name_ipch) or \
                                    (dirname == self.directory_name_dot_vs):

                                if os.path.isdir(strfilepath):
                                    os.system('attrib -r ' + parent + '\\*.* /s')  # 设置本文件夹可写
                                    os.system('attrib -r ' + strfilepath + '\\*.* /s')  # 设置父文件夹可写
                                    shutil.rmtree(strfilepath)  # 删除此文件夹
                                    print("已删除目录: {}".format(strfilepath))
            else:
                self.delete_file(file)

    def delete_file(self, file_path):
        # print("delete_file,file_path={}".format(file_path))
        # find = re.search(self.suffix_sdf + "$", file_path)  # 方式1:判断是否以.sdf结尾
        # find = file_path.endswith(self.suffix_sdf)  # 方式2:判断是否以.sdf结尾
        find = file_path[-len(self.suffix_sdf):] == self.suffix_sdf  # 方式3:判断是否以.sdf结尾
        # print("find={}".format(find))
        if find:
            os.remove(file_path)
            print("delete file: {}".format(file_path))


if __name__ == "__main__":
    delete = DeleteDirectory()
    delete.delete_directory_or_file()
