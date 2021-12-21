// audio_bitstream.ipp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2021 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <neogfx/neogfx.hpp>
#include <neogfx/audio/audio_bitstream.hpp>

namespace neogfx
{
    template <typename Interface>
    inline audio_bitstream<Interface>::audio_bitstream(audio_sample_rate aSampleRate, float aAmplitude) :
        iSampleRate{ aSampleRate }, iAmplitude{ aAmplitude }
    {
    }

    template <typename Interface>
    inline audio_bitstream<Interface>::audio_bitstream(i_audio_device const& aDevice, float aAmplitude) :
        audio_bitstream{ aDevice.data_format().sampleRate, aAmplitude }
    {
    }
    
    template <typename Interface>
    inline audio_bitstream<Interface>::~audio_bitstream()
    {
    }

    template <typename Interface>
    inline audio_sample_rate audio_bitstream<Interface>::sample_rate() const
    {
        return iSampleRate;
    }

    template <typename Interface>
    inline void audio_bitstream<Interface>::set_sample_rate(audio_sample_rate aSampleRate)
    {
        iSampleRate = aSampleRate;
    }

    
    template <typename Interface>
    inline float audio_bitstream<Interface>::amplitude(handle aHandle) const
    {
        return iAmplitude;
    }

    template <typename Interface>
    inline void audio_bitstream<Interface>::set_amplitude(handle aHandle, float aAmplitude)
    {
        iAmplitude = aAmplitude;
    }

    template <typename Interface>
    inline bool audio_bitstream<Interface>::has_envelope(handle aHandle) const
    {
        return iEnvelope != std::nullopt;
    }

    template <typename Interface>
    inline adsr_envelope const& audio_bitstream<Interface>::envelope(handle aHandle)
    {
        return iEnvelope.value();
    }

    template <typename Interface>
    inline void audio_bitstream<Interface>::clear_envelope(handle aHandle)
    {
        iEnvelope = std::nullopt;
    }

    template <typename Interface>
    inline void audio_bitstream<Interface>::set_envelope(handle aHandle, adsr_envelope const& aEnvelope)
    {
        iEnvelope = aEnvelope;
    }
}