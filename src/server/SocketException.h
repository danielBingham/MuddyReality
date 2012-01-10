/***********************************************************************************
 * File: SocketException.h
 * Definition:
 *
 * Contents:
 *
 *
 * Copyright:
 *		Copyright (C) 2009-2011 Daniel Bingham (http://www.theroadgoeson.com)
 *
 * License:
 *
 * This software is licensed under the MIT Open Source License which reads as
 * follows:
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information see here: http://www.opensource.org/licenses/mit-license.php
 *
 ***********************************************************************************/

#ifndef SOCKETEXCEPTION_H_
#define SOCKETEXCEPTION_H_

#include "Datatypes.h"

/**
 * Socket related exception classes.
 */

// General Socket Exception
class SocketException {
	public:
		SocketException(String file, String line, String m = "Exception occurred for unknown reason.") {
			locale = file + ": " + line;
			message = "SocketException at " + locale + ": " + m;
		}
		String message;
	private:
		String locale;
};

// ENETDOWN
class NetworkIsDownException: public SocketException {
	public:
		NetworkIsDownException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Network is down..." + m) {
		}
};

// EINPROGRESS
class FunctionStillWorkingException: public SocketException {
	public:
		FunctionStillWorkingException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Function is still working... " + m) {
		}
};

// EADDRINUSE
class AddressInUseException: public SocketException {
	public:
		AddressInUseException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "That address is in use... " + m) {
		}
};

// EINVAL
class InvalidSocketException: public SocketException {
	public:
		InvalidSocketException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Invalid Socket encountered... " + m) {
		}
};

// EADDRNOTAVAIL
class RemoteAddressInvalidException: public SocketException {
	public:
		RemoteAddressInvalidException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Remote address was invalid... " + m) {
		}
};

// EAFNOSUPPORT
class AddressFamilyNotSupportedException: public SocketException {
	public:
		AddressFamilyNotSupportedException(String file, String line, String m =
		        "Exception occurred for unknown reason.") :
			SocketException(file, line, "The address family is not supported... " + m) {
		}
};

// ENOBUFS
class NotEnoughMemoryInBuffersException: public SocketException {
	public:
		NotEnoughMemoryInBuffersException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Out of Memory buffers... " + m) {
		}
};

// ENOTSOCK
class NotRealSocketException: public SocketException {
	public:
		NotRealSocketException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Encountered an unreal socket... " + m) {
		}
};

// EWOULDBLOCK
class WouldBlockException: public SocketException {
	public:
		WouldBlockException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "That would block... " + m) {
		}
};

// ECONNREFUSED
class ConnectionRefusedException: public SocketException {
	public:
		ConnectionRefusedException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "The connection was refused... " + m) {
		}
};

// EFAULT
class InvalidParametersException: public SocketException {
	public:
		InvalidParametersException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "The parameters were invalid... " + m) {
		}
};

// EISCONN
class SocketAlreadyConnectedException: public SocketException {
	public:
		SocketAlreadyConnectedException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "That socket was already connected... " + m) {
		}
};

// ENETUNREACH
class DestinationAddressUnreachableException: public SocketException {
	public:
		DestinationAddressUnreachableException(String file, String line, String m =
		        "Exception occurred for unknown reason.") :
			SocketException(file, line, "The destination address wasn't reachable... " + m) {
		}
};

// ETIMEDOUT
class TimeOutException: public SocketException {
	public:
		TimeOutException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Time out occurred... " + m) {
		}
};

// EACCES
class AccessDeniedException: public SocketException {
	public:
		AccessDeniedException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Access denied... " + m) {
		}
};

// ENETRESET
class NetworkResetException: public SocketException {
	public:
		NetworkResetException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "Network was reset... " + m) {
		}
};

// ENOTCONN
class SocketNotConnectedException: public SocketException {
	public:
		SocketNotConnectedException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "That socket isn't connected... " + m) {
		}
};

// EOPNOTSUPP
class UnsupportedOperationException: public SocketException {
	public:
		UnsupportedOperationException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "That is an unsupported operation... " + m) {
		}
};

// ESHUTDOWN
class ShutdownSocketException: public SocketException {
	public:
		ShutdownSocketException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "That socket has been shutdown... " + m) {
		}
};

// EHOSTUNREACH
class HostUnreachableException: public SocketException {
	public:
		HostUnreachableException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "The host is unreachable... " + m) {
		}
};

// ECONNABORTED
class ConnectionAbortedException: public SocketException {
	public:
		ConnectionAbortedException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "The connection was aborted... " + m) {
		}
};

// ECONNRESET
class ConnectionResetException: public SocketException {
	public:
		ConnectionResetException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "The connection was reset... " + m) {
		}
};

// EMFILE
class OutOfSocketDescriptorsException: public SocketException {
	public:
		OutOfSocketDescriptorsException(String file, String line, String m = "Exception occurred for unknown reason.") :
			SocketException(file, line, "No more sockets available... " + m) {
		}
};

#endif /* SOCKETEXCEPTION_H_ */
