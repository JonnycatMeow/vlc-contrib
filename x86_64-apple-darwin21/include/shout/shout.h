/*  shout.h
 *
 *  API for libshout, the streaming library for icecast
 *
 *  Copyright (C) 2002-2003 the Icecast team <team@icecast.org>,
 *  Copyright (C) 2012-2022 Philipp Schafft <lion@lion.leolix.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef __LIBSHOUT_SHOUT_H__
#define __LIBSHOUT_SHOUT_H__

#include <sys/types.h>
#if defined(WIN32) && !defined(__MINGW64__) && !defined(__MINGW32__)
#include <os.h>
#endif

#include <stdarg.h>

/* ----------------[ Attributes ]---------------- */

/* Attributes depend on used compiler */
#if (defined(__clang__) && __clang_major__ >= 4)
#define SHOUT_ATTR_F_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#elif __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 9)
#define SHOUT_ATTR_F_DEPRECATED(msg) __attribute__ ((deprecated (msg)))
#define SHOUT_ATTR_F_WARN_UNUSED_RESULT __attribute__ ((warn_unused_result))
#endif

#ifndef SHOUT_ATTR_F_DEPRECATED
#define SHOUT_ATTR_F_DEPRECATED(msg)
#endif

#ifndef SHOUT_ATTR_F_WARN_UNUSED_RESULT
#define SHOUT_ATTR_F_WARN_UNUSED_RESULT
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* ----------------[ Constants ]---------------- */

#define SHOUTERR_SUCCESS            (  0) /* No error */
#define SHOUTERR_INSANE             ( -1) /* Nonsensical arguments e.g. self being NULL */ 
#define SHOUTERR_NOCONNECT          ( -2) /* Couldn't connect */
#define SHOUTERR_NOLOGIN            ( -3) /* Login failed */
#define SHOUTERR_SOCKET             ( -4) /* Socket error */
#define SHOUTERR_MALLOC             ( -5) /* Out of memory */
#define SHOUTERR_METADATA           ( -6)
#define SHOUTERR_CONNECTED          ( -7) /* Cannot set parameter while connected */
#define SHOUTERR_UNCONNECTED        ( -8) /* Not connected */
#define SHOUTERR_UNSUPPORTED        ( -9) /* This libshout doesn't support the requested option */
#define SHOUTERR_BUSY               (-10) /* Resource is busy, try again (later) */
#define SHOUTERR_NOTLS              (-11) /* TLS requested but not supported by peer */
#define SHOUTERR_TLSBADCERT         (-12) /* TLS connection can not be established because of bad certificate */
#define SHOUTERR_RETRY              (-13) /* Retry last operation. */

#define SHOUT_FORMAT_OGG            (  0) /* Ogg */
#define SHOUT_FORMAT_MP3            (  1) /* MP3 */
#define SHOUT_FORMAT_WEBM           (  2) /* WebM */
#define SHOUT_FORMAT_WEBMAUDIO      (  3) /* WebM, audio only, obsolete. Only used by shout_set_format() */
#define SHOUT_FORMAT_MATROSKA       (  4) /* Matroska */
#define SHOUT_FORMAT_TEXT           (  5) /* Text, must be in UTF-8, usage must be SHOUT_USAGE_TEXT. */

/* backward-compatibility alias */
#define SHOUT_FORMAT_VORBIS         SHOUT_FORMAT_OGG

/* Usages */
#define SHOUT_USAGE_AUDIO           (0x0001U) /* Audio substreams*/
#define SHOUT_USAGE_VISUAL          (0x0002U) /* Picture/Video substreams (most often combined with SHOUT_USAGE_AUDIO) */
#define SHOUT_USAGE_TEXT            (0x0004U) /* Text substreams that are not subtitles */
#define SHOUT_USAGE_SUBTITLE        (0x0008U) /* Subtitle substreams */
#define SHOUT_USAGE_LIGHT           (0x0010U) /* Light control substreams */
#define SHOUT_USAGE_UI              (0x0020U) /* User interface data, such as DVD menus or buttons */
#define SHOUT_USAGE_METADATA        (0x0040U) /* Substreams that include metadata for the stream */
#define SHOUT_USAGE_APPLICATION     (0x0080U) /* Application specific data substreams */
#define SHOUT_USAGE_CONTROL         (0x0100U) /* Substreams that control the infrastructure */
#define SHOUT_USAGE_COMPLEX         (0x0200U) /* Substreams that are themself a mixture of other types */
#define SHOUT_USAGE_OTHER           (0x0400U) /* Substream of types not listed here */
#define SHOUT_USAGE_UNKNOWN         (0x0800U) /* The stream MAY contain additional substreams of unknown nature */
#define SHOUT_USAGE_3D              (0x1000U) /* The Stream contains information for 3D playback */
#define SHOUT_USAGE_4D              (0x2000U) /* The Stream contains information for 4D/XD playback */

#define SHOUT_PROTOCOL_HTTP         (  0)
#define SHOUT_PROTOCOL_XAUDIOCAST   (  1) /* Deprecated. May be removed in future versions. Do not use. */
#define SHOUT_PROTOCOL_ICY          (  2)
#define SHOUT_PROTOCOL_ROARAUDIO    (  3)

/* Possible TLS modes */
#define SHOUT_TLS_DISABLED          (  0) /* Do not use TLS at all */
#define SHOUT_TLS_AUTO              (  1) /* Autodetect which TLS mode to use if any */
#define SHOUT_TLS_AUTO_NO_PLAIN     (  2) /* Like SHOUT_TLS_AUTO_NO_PLAIN but does not allow plain connections */
#define SHOUT_TLS_RFC2818           ( 11) /* Use TLS for transport layer like HTTPS [RFC2818] does. */
#define SHOUT_TLS_RFC2817           ( 12) /* Use TLS via HTTP Upgrade:-header [RFC2817]. */

/* Possible values for blocking */
#define SHOUT_BLOCKING_DEFAULT      (255) /* Use the default blocking setting. */
#define SHOUT_BLOCKING_FULL         (  0) /* Block in all I/O related functions */
#define SHOUT_BLOCKING_NONE         (  1) /* Do not block in I/O related functions */

#define SHOUT_AI_BITRATE            "bitrate"
#define SHOUT_AI_SAMPLERATE         "samplerate"
#define SHOUT_AI_CHANNELS           "channels"
#define SHOUT_AI_QUALITY            "quality"

#define SHOUT_META_NAME             "name"
#define SHOUT_META_URL              "url"
#define SHOUT_META_GENRE            "genre"
#define SHOUT_META_DESCRIPTION      "description"
#define SHOUT_META_IRC              "irc"
#define SHOUT_META_AIM              "aim"
#define SHOUT_META_ICQ              "icq"

#define SHOUT_CALLBACK_PASS         (  1) /* Pass the event to the next handler */

typedef enum {
    SHOUT_CONTROL__MIN = 0,
    SHOUT_CONTROL_GET_SERVER_CERTIFICATE_AS_PEM,
    SHOUT_CONTROL_GET_SERVER_CERTIFICATE_CHAIN_AS_PEM,
    SHOUT_CONTROL__MAX = 32767
} shout_control_t;

typedef enum {
    SHOUT_EVENT__MIN = 0,
    SHOUT_EVENT_TLS_CHECK_PEER_CERTIFICATE,
    SHOUT_EVENT__MAX = 32767
} shout_event_t;

typedef struct shout shout_t;
typedef struct _util_dict shout_metadata_t;

typedef int (*shout_callback_t)(shout_t *shout, shout_event_t event, void *userdata, va_list ap);


/* ----------------[ Generic ]---------------- */

/* initializes the shout library. Must be called before anything else */
void shout_init(void);

/* shuts down the shout library, deallocating any global storage. Don't call
 * anything afterwards */
void shout_shutdown(void);

/* returns a static version string.  Non-null parameters will be set to the
 * value of the library major, minor, and patch levels, respectively */
const char *shout_version(int *major, int *minor, int *patch);

/* Allocates and sets up a new shout_t.  Returns NULL if it can't get enough
 * memory.  The returns shout_t must be disposed of with shout_free. */
shout_t *shout_new(void) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Free all memory allocated by a shout_t */
void shout_free(shout_t *self);

/* Returns a statically allocated string describing the last shout error
 * to occur.  Only valid until the next libshout call on this shout_t */
const char *shout_get_error(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Return the error code (e.g. SHOUTERR_SOCKET) for this shout instance */
int shout_get_errno(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* returns SHOUTERR_CONNECTED or SHOUTERR_UNCONNECTED */
int shout_get_connected(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;


/* ----------------[ Configuration ]---------------- */
/* Parameter manipulation functions.  libshout makes copies of all parameters,
 * the caller may free its copies after giving them to libshout.  May return
 * SHOUTERR_MALLOC */

/* Connection parameters */
int shout_set_host(shout_t *self, const char *host);
const char *shout_get_host(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

int shout_set_port(shout_t *self, unsigned short port);
unsigned short shout_get_port(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

int shout_set_agent(shout_t *self, const char *agent);
const char *shout_get_agent(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* See SHOUT_TLS_* above */
int shout_set_tls(shout_t *self, int mode);
int shout_get_tls(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Set the directory for CA certs. Default: operating system's default */
int shout_set_ca_directory(shout_t *self, const char *directory);
const char *shout_get_ca_directory(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Set a CA cert file for checking. If you use a self signed server cert
 * you can pass this cert using this function for verification.
 * Default: operating system's default */
int shout_set_ca_file(shout_t *self, const char *file);
const char *shout_get_ca_file(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Set list of allowed ciphers.
 * This function should only be used in case of using an old libshout
 * after some attacks got known. Watch the icecast mailinglist for
 * known problems.
 * DO NOT SET THIS TO ANY FIXED VALUE. IF YOU USE THIS FUNCTION
 * EXPOSE IT TO THE USER. OTHERWISE YOU WILL HARM SECURITY.
 * Default: internal list of secure ciphers. */
int shout_set_allowed_ciphers(shout_t *self, const char *ciphers);
const char *shout_get_allowed_ciphers(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Authentication parameters */
int shout_set_user(shout_t *self, const char *username);
const char *shout_get_user(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

int shout_set_password(shout_t *, const char *password);
const char *shout_get_password(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Set a client certificate for TLS connections.
 * This must be in PEM format with both cert and private key in the same file.
 * Default: none. */
int shout_set_client_certificate(shout_t *self, const char *certificate);
const char *shout_get_client_certificate(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Mount parameters */
int shout_set_mount(shout_t *self, const char *mount);
const char *shout_get_mount(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Other parameters */
/* takes a SHOUT_AI_xxxx argument */
int shout_set_audio_info(shout_t *self, const char *name, const char *value);
const char *shout_get_audio_info(shout_t *self, const char *name) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* takes a SHOUT_META_xxxx argument */
int shout_set_meta(shout_t *self, const char *name, const char *value);
const char *shout_get_meta(shout_t *self, const char *name) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

int shout_set_public(shout_t *self, unsigned int make_public);
unsigned int shout_get_public(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Set the content language.
 * Values as per RFC5646 Section 2.1.
 * This lists the target audiance language(s), not the language of songs
 * (unless the station has a focus on songs in a specific language).
 * The value of NULL is allowed if the content language is not known or is expected to change.
 *
 * Examples:
 *  A German station with moderations and news in German and Gamern and international songs
 *  would generally set this to "de-DE".
 *  A similar station in Switzerland would set this to "de-CH".
 *  A station with content in Portuguese, and Klingon should set this to "pt, tlh".
 */
int shout_set_content_language(shout_t *self, const char *content_language);
const char *shout_get_content_language(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Set the format of the content to send.
 * * format is one of SHOUT_FORMAT_xxxx.
 * * usage is a bit vector composed of SHOUT_USAGE_xxxx.
 * * codecs is NULL as of this version. Future versions will also support NULL.
 */
int shout_set_content_format(shout_t *self, unsigned int format, unsigned int usage, const char *codecs);
int shout_get_content_format(shout_t *self, unsigned int *format, unsigned int *usage, const char **codecs);

/* takes a SHOUT_PROTOCOL_xxxxx argument */
int shout_set_protocol(shout_t *self, unsigned int protocol);
unsigned int shout_get_protocol(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Instructs libshout to use nonblocking I/O. Must be called before
 * shout_open (no switching back and forth midstream at the moment).
 * nonblocking is one of SHOUT_BLOCKING_xxx. */
int shout_set_nonblocking(shout_t* self, unsigned int nonblocking);
unsigned int shout_get_nonblocking(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;


/* ----------------[ Actions ]---------------- */

/* Opens a connection to the server.  All parameters must already be set */
int shout_open(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Closes a connection to the server */
int shout_close(shout_t *self);

/* Send data to the server, parsing it for format specific timing info */
int shout_send(shout_t *self, const unsigned char *data, size_t len) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Send unparsed data to the server.  Do not use this unless you know
 * what you are doing. 
 * Returns the number of bytes written, or < 0 on error.
 */
ssize_t shout_send_raw(shout_t *self, const unsigned char *data, size_t len) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* return the number of bytes currently on the write queue (only makes sense in
 * nonblocking mode). */
ssize_t shout_queuelen(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;
  
/* Puts caller to sleep until it is time to send more data to the server */
void shout_sync(shout_t *self);

/* Amount of time in ms caller should wait before sending again */
int shout_delay(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT;


/* ----------------[ MP3/AAC ONLY ]---------------- */
/* Functions in this block are for use with MP3, and AAC streams only */

/* Sets MP3 metadata.
 * Returns one of SHOUTERR_XXX.
 *
 * Note: This function is for MP3 streams only.
 *
 * The metadata passed must have been added as UTF-8 using shout_metadata_add().
 */
int shout_set_metadata_utf8(shout_t *self, shout_metadata_t *metadata) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Allocates a new metadata structure.  Must be freed by shout_metadata_free. */
shout_metadata_t *shout_metadata_new(void) SHOUT_ATTR_F_WARN_UNUSED_RESULT;

/* Free resources allocated by shout_metadata_t */
void shout_metadata_free(shout_metadata_t *self);

/* Add a parameter to the metadata structure.
 * Returns:
 *   SHOUTERR_SUCCESS on success
 *   SHOUTERR_INSANE if self isn't a valid shout_metadata_t* or name is null
 *   SHOUTERR_MALLOC if memory can't be allocated */
int shout_metadata_add(shout_metadata_t *self, const char *name, const char *value) SHOUT_ATTR_F_WARN_UNUSED_RESULT;


/* ----------------[ Advanced ]---------------- */
/* Advanced. Do not use. */

int shout_control(shout_t *self, shout_control_t control, ...) SHOUT_ATTR_F_WARN_UNUSED_RESULT;
int shout_set_callback(shout_t *self, shout_callback_t callback, void *userdata);


/* ----------------[ Obsolete ]---------------- */
/* Those functions are obsolete and MUST NOT be used in newer software.
 * They may be removed with any future version.
 */

int shout_set_name(shout_t *self, const char *name) SHOUT_ATTR_F_DEPRECATED("use shout_set_meta() with SHOUT_META_NAME"); // obsolete
const char *shout_get_name(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("use shout_get_meta() with SHOUT_META_NAME"); // obsolete

int shout_set_url(shout_t *self, const char *url) SHOUT_ATTR_F_DEPRECATED("use shout_set_meta() with SHOUT_META_URL"); // obsolete
const char *shout_get_url(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("use shout_get_meta() with SHOUT_META_URL"); // obsolete

int shout_set_genre(shout_t *self, const char *genre) SHOUT_ATTR_F_DEPRECATED("use shout_set_meta() with SHOUT_META_GENRE"); // obsolete
const char *shout_get_genre(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("use shout_get_meta() with SHOUT_META_GENRE"); // obsolete

int shout_set_description(shout_t *self, const char *description) SHOUT_ATTR_F_DEPRECATED("use shout_set_meta() with SHOUT_META_DESCRIPTION"); // obsolete
const char *shout_get_description(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("use shout_get_meta() with SHOUT_META_DESCRIPTION"); // obsolete

/* takes a SHOUT_FORMAT_xxxx argument */
int shout_set_format(shout_t *self, unsigned int format) SHOUT_ATTR_F_DEPRECATED("Use shout_set_content_format()"); // obsolete
unsigned int shout_get_format(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("use shout_get_content_format()"); // obsolete

int shout_set_dumpfile(shout_t *self, const char *dumpfile) SHOUT_ATTR_F_DEPRECATED("Only useful with SHOUT_PROTOCOL_XAUDIOCAST which is deprecated."); // obsolete
const char *shout_get_dumpfile(shout_t *self) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("Only useful with SHOUT_PROTOCOL_XAUDIOCAST which is deprecated."); // obsolete

int shout_set_metadata(shout_t *self, shout_metadata_t *metadata) SHOUT_ATTR_F_WARN_UNUSED_RESULT SHOUT_ATTR_F_DEPRECATED("Use shout_set_metadata_utf8()");

#ifdef __cplusplus
}
#endif

/* --- Compiled features --- */

#define SHOUT_THREADSAFE 1
#define SHOUT_TLS        0

#endif /* __LIBSHOUT_SHOUT_H__ */
