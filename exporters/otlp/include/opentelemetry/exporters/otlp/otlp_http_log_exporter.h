// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifdef ENABLE_LOGS_PREVIEW

#  include "opentelemetry/sdk/logs/exporter.h"

#  include "opentelemetry/exporters/otlp/otlp_http_client.h"

#  include "opentelemetry/exporters/otlp/otlp_environment.h"
#  include "opentelemetry/exporters/otlp/otlp_http_log_exporter_options.h"

#  include <chrono>
#  include <cstddef>
#  include <memory>
#  include <string>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace otlp
{

/**
 * The OTLP exporter exports log data in OpenTelemetry Protocol (OTLP) format.
 */
class OtlpHttpLogExporter final : public opentelemetry::sdk::logs::LogExporter
{
public:
  /**
   * Create an OtlpHttpLogExporter with default exporter options.
   */
  OtlpHttpLogExporter();

  /**
   * Create an OtlpHttpLogExporter with user specified options.
   * @param options An object containing the user's configuration options.
   */
  OtlpHttpLogExporter(const OtlpHttpLogExporterOptions &options);

  /**
   * Creates a recordable that stores the data in a JSON object
   */
  std::unique_ptr<opentelemetry::sdk::logs::Recordable> MakeRecordable() noexcept override;

  /**
   * Exports a vector of log records to the Elasticsearch instance. Guaranteed to return after a
   * timeout specified from the options passed from the constructor.
   * @param records A list of log records to send to Elasticsearch.
   */
  opentelemetry::sdk::common::ExportResult Export(
      const nostd::span<std::unique_ptr<opentelemetry::sdk::logs::Recordable>> &records) noexcept
      override;

  /**
   * Shutdown this exporter.
   * @param timeout The maximum time to wait for the shutdown method to return
   */
  bool Shutdown(
      std::chrono::microseconds timeout = std::chrono::microseconds::max()) noexcept override;

private:
  // Configuration options for the exporter
  const OtlpHttpLogExporterOptions options_;

  // Object that stores the HTTP sessions that have been created
  std::unique_ptr<OtlpHttpClient> http_client_;
  // For testing
  friend class OtlpHttpLogExporterTestPeer;
  /**
   * Create an OtlpHttpLogExporter using the specified http client.
   * Only tests can call this constructor directly.
   * @param http_client the http client to be used for exporting
   */
  OtlpHttpLogExporter(std::unique_ptr<OtlpHttpClient> http_client);
};
}  // namespace otlp
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
#endif
