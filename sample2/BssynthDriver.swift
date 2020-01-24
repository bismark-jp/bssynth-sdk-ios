//
//  BssynthDriver.swift
//  sample2
//
//  Copyright © 2020 bismark LLC. All rights reserved.
//

import Foundation

class BssynthDriver {

    static let shared: BssynthDriver = {
        let instance = BssynthDriver()
        return instance
    }()

    private let api = bsmdLoad()!
    private var handle: BSMD_HANDLE? = nil
    
    private let port = UInt8(0)

    public func initialize() {
        let library = Bundle.main.path(forResource: "GeneralUser GS SoftSynth v1.44", ofType: "sf2")!

        var err = api.pointee.initializeWithSoundLib(
            &handle,
            { handle, type, data, user in
                switch type {
                    case BSMD_CALLBACK_TYPE_OPEN:
                        print("opened")
                    case BSMD_CALLBACK_TYPE_CLOSE:
                        print("closeed")
                    case BSMD_CALLBACK_TYPE_START:
                        print("started")
                    case BSMD_CALLBACK_TYPE_STOP:
                        print("stopped")
                    default:
                        break
                }
            },
            nil, // pointer for callback (not used here)
            library.cString(using: .utf8),
            nil,
            bssynth_key
        )
        if err == BSMD_OK {
            var regions = Int32(512)
            err = api.pointee.ctrl(handle, BSMD_CTRL_SET_NUMBER_OF_REGIONS, &regions, regions.byteWidth)
        }

        if err != BSMD_OK {
            print("ERROR - initialize synthesizer")
        }
    }

    public func exit() {
        if api.pointee.exit(handle) != BSMD_OK {
            print("ERROR - finilize synthesizer")
        }
    }
    
    public func open() {
        if api.pointee.open(handle, nil, nil) != BSMD_OK {
            print("ERROR - open")
        }
    }

    public func close() {
        if api.pointee.close(handle) != BSMD_OK {
            print("ERROR - close")
        }
    }

    public func start() {
        if api.pointee.start(handle) != BSMD_OK {
            print("ERROR - start")
        }
    }

    public func stop() {
        if api.pointee.stop(handle) != BSMD_OK {
            print("ERROR - stop")
        }
    }

    public var isPlaying: Bool {
        return api.pointee.isPlaying(handle) == 1
    }

    public var reverb: Bool {
        set {
            var value: Int32 = newValue ? 1 : 0
            if api.pointee.ctrl(handle, BSMD_CTRL_SET_REVERB, &value, value.byteWidth) != BSMD_OK {
                print("ERROR - set reverb = \(newValue)")
            }
        }
        get {
            var value = 0
            if api.pointee.ctrl(handle, BSMD_CTRL_GET_REVERB, &value, value.byteWidth) != BSMD_OK {
                print("ERROR - get reverb")
            }
            return value == 1
        }
    }
    public var chorus: Bool {
        set {
            var value: Int32 = newValue ? 1 : 0
            if api.pointee.ctrl(handle, BSMD_CTRL_SET_CHORUS, &value, value.byteWidth) != BSMD_OK {
                print("ERROR - set chorus = \(newValue)")
            }
        }
        get {
            var value = 0
            if api.pointee.ctrl(handle, BSMD_CTRL_GET_CHORUS, &value, value.byteWidth) != BSMD_OK {
                print("ERROR - get chorus")
            }
            return value == 1
        }
    }

    public func setChannnelMessage(status: UInt8, data1: UInt8, data2: UInt8) {
        print(String(format: "%02X %02X %02X", status, data1, data2))
        api.pointee.setChannelMessage(handle, port, status, data1, data2)
    }

    public func currentProgramName(channel: UInt8) -> String {
        let data = UnsafeMutableBufferPointer<CChar>.allocate(capacity: 64)
        defer {
          data.deallocate()
        }
        _ = self.api.pointee.ctrl(
            self.handle,
            BSMD_CTRL(BSMD_CTRL_GET_INSTRUMENT_NAME.rawValue + UInt32(port * 16 + channel)),
            data.baseAddress!,
            64
        )
        let name = String(cString: data.baseAddress!, encoding: .ascii) ?? ""
        return name
    }
}

extension FixedWidthInteger {
    var byteWidth: Int32 {
        return Int32(self.bitWidth / UInt8.bitWidth)
    }

    static var byteWidth: Int32 {
        return Int32(Self.bitWidth / UInt8.bitWidth)
    }
}
