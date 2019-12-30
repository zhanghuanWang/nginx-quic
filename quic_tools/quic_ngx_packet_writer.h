
/*
 * Copyright (C) sunlei
 */

#ifndef QUICHE_QUIC_CORE_QUIC_NGX_PACKET_WRITER_H_
#define QUICHE_QUIC_CORE_QUIC_NGX_PACKET_WRITER_H_

#include "net/third_party/quiche/src/quic/core/quic_default_packet_writer.h"
#include "net/quic/platform/impl/quic_linux_socket_utils.h"

namespace quic {

constexpr size_t kMaxWritesCacheCount = 16;
constexpr size_t kMaxWritesCacheSize = 2 * kMaxOutgoingPacketSize;
  
// Ngx packet writer which wraps QuicLinuxSocketUtils WritePacket.
class QUIC_EXPORT_PRIVATE QuicNgxPacketWriter : public QuicDefaultPacketWriter {
 public:
  explicit QuicNgxPacketWriter(int fd);
  QuicNgxPacketWriter(const QuicNgxPacketWriter&) = delete;
  QuicNgxPacketWriter& operator=(const QuicNgxPacketWriter&) = delete;
  ~QuicNgxPacketWriter() override;

  // QuicPacketWriter
  WriteResult WritePacket(const char* buffer,
                          size_t buf_len,
                          const QuicIpAddress& self_address,
                          const QuicSocketAddress& peer_address,
                          PerPacketOptions* options) override;
  WriteResult Flush() override;

 private:
  QuicDeque<BufferedWrite> buffered_writes_;
  char writes_cache_[kMaxWritesCacheCount][kMaxWritesCacheSize];
  size_t writes_cache_pos_;
  // QuicSyscallWrapper quic_sys_call_wrapper_;
};

}  // namespace quic

#endif  // QUICHE_QUIC_CORE_QUIC_NGX_PACKET_WRITER_H_
