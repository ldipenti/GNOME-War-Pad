# CaseInsensitiveFile class: search for a name with similar filename. This is
# because VGAP files usually come from DOS environments.

import gnomevfs
import sre

class CaseInsensitiveFile(gnomevfs.Handle):
    '''
    Search for a file name which can be case swapped
    '''
    def __init__(self, filename):
        uri = gnomevfs.URI(filename)
        # Get parent dir contents
        files = []
        for f in gnomevfs.DirectoryHandle(uri.dirname):
            files.append(f)
        # Collect similar file names
        matches = []
        for f in files:
            regex = uri.short_name.replace('.', '\.')
            if sre.search(regex, f.name, sre.IGNORECASE):
                matches.append(f)
        # Check for unique match
        if len(matches) == 1:
            print "Found: " + matches[0].name
            real_uri = gnomevfs.URI(uri.dirname + '/' + matches[0].name)
            super(CaseInsensitiveFile, self).__init__(real_uri)
        else:
            print "OUCH! found " + str(len(matches)) + " matches"
            raise gnomevfs.NotFoundError, "There were zero or more than one matches on your file name"
        return
    pass
