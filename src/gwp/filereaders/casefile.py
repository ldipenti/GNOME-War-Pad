# CaseInsensitiveFile class: search for a name with similar filename. This is
# because VGAP files usually come from DOS environments.

#import gnomevfs
import sre
import os.path
import os

## Buggy code, maybe GnomeVFS's fault??
#class CaseInsensitiveFileVFS(gnomevfs.Handle):
#    '''
#     Search for a file name which can be case swapped
#     '''
#     def __init__(self, filename):
#         uri = gnomevfs.URI(filename)
#         # Get parent dir contents
#         files = []
#         for f in gnomevfs.DirectoryHandle(uri.parent):
#             files.append(f)
#         # Collect similar file names
#         matches = []
#         for f in files:
#             regex = uri.short_name.replace('.', '\.')
#             if sre.search(regex, f.name, sre.IGNORECASE):
#                 matches.append(f)
#         # Check for unique match
#         if len(matches) == 1:
#             print "Found: " + matches[0].name
#             real_uri = gnomevfs.URI(str(uri.parent) + '/' + matches[0].name)
#             super(CaseInsensitiveFile, self).__init__(real_uri)
#             self.size = self.get_file_info().size
#         else:
#             print "OUCH! found " + str(len(matches)) + " matches"
#             raise gnomevfs.NotFoundError, "There were zero or more than one matches on your file name"
#         return
#     pass

class NotFoundError(Exception):
    def __init__(self, msg):
        self.value = msg
        return

    def __str__(self):
        return repr(self.value)
    pass

class CaseInsensitiveFileNOVFS(file):
    def __init__(self, filename):
        files = os.listdir(os.path.dirname(filename))

        matches = []
        for f in files:
            regex = os.path.basename(filename).replace('.', '\.')
            if sre.search(regex, f, sre.IGNORECASE):
                matches.append(f)
        # Check for unique match
        if len(matches) == 1:
            print "Found: " + matches[0]
            real_uri = os.path.dirname(filename) + '/' + matches[0]
            super(CaseInsensitiveFileNOVFS, self).__init__(real_uri)
            self.size = os.path.getsize(real_uri)
        else:
            print "OUCH! found " + str(len(matches)) + " matches"
            raise NotFoundError, "There were zero or more than one matches on your file name: " + filename
        return
    pass

class CaseInsensitiveFile(CaseInsensitiveFileNOVFS):
    '''
    Abstract class: VFS version is not working correctly (gnomevfs broken?),
    so we will provide a similar version accessing local files only
    '''
    pass
